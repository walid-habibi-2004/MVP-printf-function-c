#define _POSIX_C_SOURCE 200809L

#include "ft_printf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OUTPUT_CAPACITY 4096

static int g_tests_run;
static int g_tests_passed;

/* Redirect stdout to a temporary file to compare raw output bytes. */
static int capture_start(FILE **capture_file, int *saved_stdout)
{
	if (fflush(stdout) == EOF)
		return (0);
	*capture_file = tmpfile();
	if (*capture_file == NULL)
		return (0);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		fclose(*capture_file);
		*capture_file = NULL;
		return (0);
	}
	if (dup2(fileno(*capture_file), STDOUT_FILENO) == -1)
	{
		close(*saved_stdout);
		fclose(*capture_file);
		*capture_file = NULL;
		*saved_stdout = -1;
		return (0);
	}
	clearerr(stdout);
	return (1);
}

static int capture_finish(FILE *capture_file, int saved_stdout,
		unsigned char *output, size_t capacity, size_t *output_length)
{
	long	file_size;
	int		ok;

	ok = 1;
	*output_length = 0;
	if (fflush(stdout) == EOF)
		ok = 0;
	if (fseek(capture_file, 0, SEEK_END) != 0)
		ok = 0;
	file_size = ftell(capture_file);
	if (file_size < 0 || (unsigned long)file_size > (unsigned long)capacity)
		ok = 0;
	else if (fseek(capture_file, 0, SEEK_SET) != 0)
		ok = 0;
	else
	{
		*output_length = fread(output, 1, (size_t)file_size, capture_file);
		if (*output_length != (size_t)file_size)
			ok = 0;
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		ok = 0;
	if (close(saved_stdout) == -1)
		ok = 0;
	clearerr(stdout);
	if (fclose(capture_file) == EOF)
		ok = 0;
	return (ok);
}

#define CAPTURE_CALL(expression, result, output, output_length, capture_ok) \
	do \
	{ \
		FILE *capture_file; \
		int saved_stdout; \
		(output_length) = 0; \
		(capture_ok) = capture_start(&capture_file, &saved_stdout); \
		if (capture_ok) \
		{ \
			(result) = (expression); \
			(capture_ok) = capture_finish(capture_file, saved_stdout, \
				(output), sizeof(output), &(output_length)); \
		} \
		else \
			(result) = -1; \
	} while (0)

static void print_escaped(const unsigned char *bytes, size_t length)
{
	size_t	i;
	unsigned char c;

	fputc('"', stderr);
	i = 0;
	while (i < length)
	{
		c = bytes[i];
		if (c == '\0')
			fputs("\\0", stderr);
		else if (c == '\n')
			fputs("\\n", stderr);
		else if (c == '\r')
			fputs("\\r", stderr);
		else if (c == '\t')
			fputs("\\t", stderr);
		else if (c == '\\')
			fputs("\\\\", stderr);
		else if (c == '"')
			fputs("\\\"", stderr);
		else if (c >= 0x20 && c <= 0x7e)
			fputc(c, stderr);
		else
			fprintf(stderr, "\\x%02X", (unsigned int)c);
		i++;
	}
	fputc('"', stderr);
}

static int compare_test(int number, const char *description,
		int ft_capture_ok, int ft_return, const unsigned char *ft_output,
		size_t ft_length, int libc_capture_ok, int libc_return,
		const unsigned char *libc_output, size_t libc_length)
{
	int output_equal;
	int returns_equal;
	int ft_count_ok;
	int libc_count_ok;
	int passed;

	g_tests_run++;
	output_equal = (ft_length == libc_length
			&& memcmp(ft_output, libc_output, ft_length) == 0);
	returns_equal = (ft_return == libc_return);
	ft_count_ok = (ft_capture_ok && ft_return >= 0
			&& (size_t)ft_return == ft_length);
	libc_count_ok = (libc_capture_ok && libc_return >= 0
			&& (size_t)libc_return == libc_length);
	passed = (ft_capture_ok && libc_capture_ok && output_equal
			&& returns_equal && ft_count_ok && libc_count_ok);
	if (passed)
		g_tests_passed++;
	fprintf(stderr, "Test %02d - %s: %s\n", number, description,
			passed ? "PASSED" : "FAILED");
	fprintf(stderr, "  output expected -> got: ");
	print_escaped(libc_output, libc_length);
	fputs(" -> ", stderr);
	print_escaped(ft_output, ft_length);
	fputc('\n', stderr);
	fprintf(stderr, "  byte count expected -> got: %zu -> %zu\n",
			libc_length, ft_length);
	fprintf(stderr, "  return value expected -> got: %d -> %d\n",
			libc_return, ft_return);
	fprintf(stderr, "  return equals captured bytes: printf=%s, ft_printf=%s\n\n",
			libc_count_ok ? "yes" : "NO",
			ft_count_ok ? "yes" : "NO");
	return (passed);
}

#define RUN_TEST0(number, description, format) \
	do \
	{ \
		unsigned char ft_output[OUTPUT_CAPACITY] = {0}; \
		unsigned char libc_output[OUTPUT_CAPACITY] = {0}; \
		size_t ft_length = 0; \
		size_t libc_length = 0; \
		int ft_return = -1; \
		int libc_return = -1; \
		int ft_capture_ok = 0; \
		int libc_capture_ok = 0; \
		CAPTURE_CALL(ft_printf(format), ft_return, ft_output, ft_length, \
			ft_capture_ok); \
		CAPTURE_CALL(printf(format), libc_return, libc_output, libc_length, \
			libc_capture_ok); \
		compare_test(number, description, ft_capture_ok, ft_return, ft_output, \
			ft_length, libc_capture_ok, libc_return, libc_output, libc_length); \
	} while (0)

#define RUN_TEST1(number, description, format, arg1) \
	do \
	{ \
		unsigned char ft_output[OUTPUT_CAPACITY] = {0}; \
		unsigned char libc_output[OUTPUT_CAPACITY] = {0}; \
		size_t ft_length = 0; \
		size_t libc_length = 0; \
		int ft_return = -1; \
		int libc_return = -1; \
		int ft_capture_ok = 0; \
		int libc_capture_ok = 0; \
		CAPTURE_CALL(ft_printf(format, arg1), ft_return, ft_output, ft_length, \
			ft_capture_ok); \
		CAPTURE_CALL(printf(format, arg1), libc_return, libc_output, \
			libc_length, libc_capture_ok); \
		compare_test(number, description, ft_capture_ok, ft_return, ft_output, \
			ft_length, libc_capture_ok, libc_return, libc_output, libc_length); \
	} while (0)

#define RUN_TEST2(number, description, format, arg1, arg2) \
	do \
	{ \
		unsigned char ft_output[OUTPUT_CAPACITY] = {0}; \
		unsigned char libc_output[OUTPUT_CAPACITY] = {0}; \
		size_t ft_length = 0; \
		size_t libc_length = 0; \
		int ft_return = -1; \
		int libc_return = -1; \
		int ft_capture_ok = 0; \
		int libc_capture_ok = 0; \
		CAPTURE_CALL(ft_printf(format, arg1, arg2), ft_return, ft_output, \
			ft_length, ft_capture_ok); \
		CAPTURE_CALL(printf(format, arg1, arg2), libc_return, libc_output, \
			libc_length, libc_capture_ok); \
		compare_test(number, description, ft_capture_ok, ft_return, ft_output, \
			ft_length, libc_capture_ok, libc_return, libc_output, libc_length); \
	} while (0)

int main(void)
{
	int number;
	char character;
	char array[4];
	char empty_format[] = "";
	struct sample_type { int value; char letter; } sample;
	void *int_pointer;
	void *char_pointer;
	void *array_pointer;
	void *element_pointer;
	void *one_past_pointer;
	void *struct_pointer;

	number = 42;
	character = 'Q';
	memcpy(array, "abc", 4);
	sample.value = -17;
	sample.letter = 'S';
	int_pointer = (void *)&number;
	char_pointer = (void *)&character;
	array_pointer = (void *)array;
	element_pointer = (void *)&array[2];
	one_past_pointer = (void *)(array + sizeof(array));
	struct_pointer = (void *)&sample;

	/* %p: compare pointer text against libc; its format varies by platform. */
	// Test 1: %p formats a null pointer passed with the correct void * type.
	RUN_TEST1(1, "%p prints a null pointer", "[%p]", (void *)0);
	// Test 2: %p formats the address of an int object.
	RUN_TEST1(2, "%p prints an int object's address", "%p", int_pointer);
	// Test 3: %p formats the address of a char object.
	RUN_TEST1(3, "%p prints a char object's address", "%p", char_pointer);
	// Test 4: %p formats the start address of an array.
	RUN_TEST1(4, "%p prints an array's address", "%p", array_pointer);
	// Test 5: %p formats the address of an array element.
	RUN_TEST1(5, "%p prints an interior array-element address", "%p",
		element_pointer);
	// Test 6: %p prints a one-past-the-end pointer without dereferencing it.
	RUN_TEST1(6, "%p prints a one-past-the-end pointer", "%p",
		one_past_pointer);
	// Test 7: %p formats the address of a structure object.
	RUN_TEST1(7, "%p prints a structure object's address", "%p",
		struct_pointer);
	// Test 8: %p preserves surrounding literal text.
	RUN_TEST1(8, "%p preserves prefix and suffix text", "ptr=(%p)!",
		int_pointer);
	// Test 9: two %p conversions print two different object pointers in order.
	RUN_TEST2(9, "two %p conversions print distinct addresses", "%p %p",
		int_pointer, char_pointer);
	// Test 10: repeated %p conversions can print the same pointer twice.
	RUN_TEST2(10, "two %p conversions print the same address", "%p/%p",
		array_pointer, array_pointer);
	// Test 11: %p remains correct when a null pointer is surrounded by text.
	RUN_TEST1(11, "%p null pointer with surrounding text", "null=[%p]",
		(void *)0);
	// Test 12: %p handles adjacent conversions without separators.
	RUN_TEST2(12, "adjacent %p conversions", "%p%p", int_pointer,
		struct_pointer);

	/* %%: emit a literal percent sign; it consumes no argument. */
	// Test 13: %% emits exactly one percent sign.
	RUN_TEST0(13, "%% emits one literal percent", "%%");
	// Test 14: four percent characters in the format produce two percent signs.
	RUN_TEST0(14, "%%%% emits two literal percent signs", "%%%%");
	// Test 15: six percent characters in the format produce three percent signs.
	RUN_TEST0(15, "six percent characters emit three percent signs", "%%%%%%");
	// Test 16: %% works at the beginning of a format string.
	RUN_TEST0(16, "%% at the beginning of the format", "%%start");
	// Test 17: %% works at the end of a format string.
	RUN_TEST0(17, "%% at the end of the format", "end%%");
	// Test 18: %% works between ordinary text.
	RUN_TEST0(18, "%% embedded between ordinary text", "100%% complete");
	// Test 19: %% followed by d is literal %d, not an integer conversion.
	RUN_TEST0(19, "%%d prints the literal text %d", "%%d");
	// Test 20: %% is parsed first, then %d consumes its integer argument.
	RUN_TEST1(20, "%%%d emits a percent then a decimal integer", "%%%d", -42);
	// Test 21: a literal percent can appear before and after a %p conversion.
	RUN_TEST1(21, "%% around a %p conversion", "%%[%p]%%", int_pointer);
	// Test 22: %% and %p can appear together with ordinary text.
	RUN_TEST1(22, "%% and %p mixed with text", "address=%p (100%%)",
		struct_pointer);
	// Test 23: %p immediately followed by %% works without a separator.
	RUN_TEST1(23, "%p immediately followed by %%", "%p%%", char_pointer);
	// Test 24: %% immediately followed by %p works without a separator.
	RUN_TEST1(24, "%% immediately followed by %p", "%%%p", array_pointer);
	// Test 25: an empty format writes zero bytes and returns zero.
	RUN_TEST0(25, "empty format writes zero bytes", empty_format);

	fprintf(stderr, "Summary: %d/%d tests passed.\n", g_tests_passed,
		g_tests_run);
	if (g_tests_passed != g_tests_run)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}