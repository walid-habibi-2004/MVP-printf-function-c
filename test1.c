#define _POSIX_C_SOURCE 200809L

#include "ft_printf.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OUTPUT_CAPACITY 4096

static int g_tests_run;
static int g_tests_passed;

/*
 * Redirect stdout to a temporary file so ft_printf and libc printf can be
 * tested independently. This also lets the harness compare raw bytes, not
 * just C strings (important for %c with '\0').
 */
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

#define RUN_TEST(number, description, format, ...) \
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
		CAPTURE_CALL(ft_printf(format, __VA_ARGS__), ft_return, ft_output, \
			ft_length, ft_capture_ok); \
		CAPTURE_CALL(printf(format, __VA_ARGS__), libc_return, libc_output, \
			libc_length, libc_capture_ok); \
		compare_test(number, description, ft_capture_ok, ft_return, \
			ft_output, ft_length, libc_capture_ok, libc_return, libc_output, \
			libc_length); \
	} while (0)

int main(void)
{
	char empty[] = "";
	char one_char[] = "Z";
	char spaces[] = "   ";
	char whitespace[] = "line 1\nline 2\tend";
	char embedded_nul[] = {'A', 'B', '\0', 'C', 'D', '\0'};
	char long_text[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
		"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	/* %d and %i: signed decimal integers and int boundaries. */
	// Test 1: %d prints zero.
	RUN_TEST(1, "%d prints zero", "%d", 0);
	// Test 2: %d prints a positive integer.
	RUN_TEST(2, "%d prints a positive integer", "%d", 42);
	// Test 3: %d prints a negative integer.
	RUN_TEST(3, "%d prints a negative integer", "%d", -42);
	// Test 4: %d prints minus one correctly.
	RUN_TEST(4, "%d prints -1", "%d", -1);
	// Test 5: %d handles INT_MAX.
	RUN_TEST(5, "%d handles INT_MAX", "%d", INT_MAX);
	// Test 6: %d handles INT_MIN without signed overflow.
	RUN_TEST(6, "%d handles INT_MIN", "%d", INT_MIN);
	// Test 7: %i prints zero.
	RUN_TEST(7, "%i prints zero", "%i", 0);
	// Test 8: %i prints a positive integer.
	RUN_TEST(8, "%i prints a positive integer", "%i", 12345);
	// Test 9: %i prints a negative integer.
	RUN_TEST(9, "%i prints a negative integer", "%i", -12345);
	// Test 10: %i handles INT_MAX.
	RUN_TEST(10, "%i handles INT_MAX", "%i", INT_MAX);
	// Test 11: %i handles INT_MIN without negating it unsafely.
	RUN_TEST(11, "%i handles INT_MIN", "%i", INT_MIN);
	// Test 12: %d and %i work together in one call.
	RUN_TEST(12, "%d and %i in one format", "d=%d, i=%i", -7, 8);
	// Test 13: adjacent %d/%i conversions consume arguments in order.
	RUN_TEST(13, "adjacent %d and %i conversions", "%d%i%d%i",
		INT_MIN, -1, 0, INT_MAX);
	// Test 14: literal text before and after a signed conversion is preserved.
	RUN_TEST(14, "literal text around %d", "value=[%d]!", 2026);

	/* %c: one-byte output, including whitespace and a NUL byte. */
	// Test 15: %c prints an ordinary character.
	RUN_TEST(15, "%c prints an ordinary character", "%c", 'A');
	// Test 16: %c preserves a space character.
	RUN_TEST(16, "%c prints a space", "[%c]", ' ');
	// Test 17: %c emits a newline byte.
	RUN_TEST(17, "%c emits newline", "%c", '\n');
	// Test 18: %c emits a tab byte.
	RUN_TEST(18, "%c emits tab", "%c", '\t');
	// Test 19: %c emits NUL; comparison must be byte-based, not strcmp-based.
	RUN_TEST(19, "%c emits a NUL byte", "A%cB", '\0');
	// Test 20: %c emits the DEL byte (0x7f).
	RUN_TEST(20, "%c emits 0x7f", "%c", 0x7f);
	// Test 21: %c handles the maximum unsigned-char value.
	RUN_TEST(21, "%c emits UCHAR_MAX", "%c", (int)UCHAR_MAX);
	// Test 22: multiple %c conversions include a NUL between visible bytes.
	RUN_TEST(22, "multiple %c conversions with embedded NUL", "%c%c%c",
		'A', '\0', 'B');
	// Test 23: multiple %c conversions preserve whitespace and order.
	RUN_TEST(23, "multiple %c conversions with whitespace", "%c%c%c",
		' ', '\n', 'Z');

	/* %s: ordinary strings, empty strings, whitespace, and string termination. */
	// Test 24: %s prints a normal string.
	RUN_TEST(24, "%s prints a normal string", "%s", "Hello, world!");
	// Test 25: %s prints an empty string as zero bytes.
	RUN_TEST(25, "%s handles an empty string", "%s", empty);
	// Test 26: %s prints a one-character string.
	RUN_TEST(26, "%s prints a one-character string", "%s", one_char);
	// Test 27: %s preserves spaces inside the string.
	RUN_TEST(27, "%s preserves spaces", "[%s]", spaces);
	// Test 28: %s preserves newline and tab bytes.
	RUN_TEST(28, "%s preserves whitespace bytes", "%s", whitespace);
	// Test 29: %s stops at the first NUL in a character array.
	RUN_TEST(29, "%s stops at embedded NUL", "%s", embedded_nul);
	// Test 30: %s prints a longer string without truncation.
	RUN_TEST(30, "%s prints a longer string", "%s", long_text);
	// Test 31: multiple %s conversions consume strings in the correct order.
	RUN_TEST(31, "multiple %s conversions", "%s | %s | %s",
		"first", empty, "third");
	// Test 32: empty %s between literal text does not remove either literal.
	RUN_TEST(32, "empty %s between literal text", "left%sright", empty);

	/* %x and %X: unsigned hexadecimal output and letter casing. */
	// Test 33: %x prints zero.
	RUN_TEST(33, "%x prints zero", "%x", 0U);
	// Test 34: %x prints a small positive value.
	RUN_TEST(34, "%x prints one", "%x", 1U);
	// Test 35: %x handles the digit-to-letter boundary (0xf).
	RUN_TEST(35, "%x handles 0xf", "%x", 0xFU);
	// Test 36: %x handles the next hexadecimal place (0x10).
	RUN_TEST(36, "%x handles 0x10", "%x", 0x10U);
	// Test 37: %x prints byte value 0xff in lowercase.
	RUN_TEST(37, "%x prints 0xff", "%x", 0xFFU);
	// Test 38: %x uses lowercase a-f for a value containing hexadecimal letters.
	RUN_TEST(38, "%x uses lowercase letters", "%x", 0xABCDEF01U);
	// Test 39: %x handles a value with the highest unsigned-int bit set.
	RUN_TEST(39, "%x handles the highest unsigned-int bit",
		"%x", UINT_MAX / 2U + 1U);
	// Test 40: %x handles UINT_MAX.
	RUN_TEST(40, "%x handles UINT_MAX", "%x", UINT_MAX);
	// Test 41: %X prints zero.
	RUN_TEST(41, "%X prints zero", "%X", 0U);
	// Test 42: %X uses uppercase A-F.
	RUN_TEST(42, "%X uses uppercase letters", "%X", 0xABCDEF01U);
	// Test 43: %X handles UINT_MAX.
	RUN_TEST(43, "%X handles UINT_MAX", "%X", UINT_MAX);
	// Test 44: %x and %X show different casing for the same value.
	RUN_TEST(44, "%x and %X casing in one call", "lower=%x upper=%X",
		0xABCDEF01U, 0xABCDEF01U);
	// Test 45: multiple hexadecimal conversions preserve argument order.
	RUN_TEST(45, "multiple %x/%X values", "%x,%X,%x",
		0U, UINT_MAX, 0x1234ABCDU);

#if defined(FT_PRINTF_TEST_GLIBC_NULL_STRING)
	/*
	 * Optional, non-portable test: ISO C leaves printf("%s", NULL) undefined.
	 * Enable this only on a libc known to print a placeholder for NULL strings.
	 * A broken ft_printf may crash here; this case is not part of the default run.
	 */
	{
		char *null_string = NULL;

		// Test 46: optional libc-specific behavior for a NULL %s argument.
		RUN_TEST(46, "optional NULL %s behavior (non-portable)", "%s",
			null_string);
	}
#endif

	fprintf(stderr, "Summary: %d/%d tests passed.\n",
			g_tests_passed, g_tests_run);
	if (g_tests_passed == g_tests_run)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}