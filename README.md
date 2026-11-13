*This project has been created as part of the 42 curriculum by wahabibi.*

# ft_printf

## Description

**ft_printf** is a re-implementation of the C standard `printf` function. The goal is to learn how to write a **variadic function** (`<stdarg.h>`), how to parse a format string, and how to build a small, reusable static library (`libftprintf.a`).

The function has the same prototype as the original:

```c
int ft_printf(const char *format, ...);
```

It writes to the standard output and returns the **number of characters printed**, or `-1` if a `write` error occurs.

### Supported conversions

| Conversion | Output |
|:---:|---|
| `%c` | a single character |
| `%s` | a string (`(null)` if the pointer is `NULL`) |
| `%p` | a pointer in hexadecimal (`0x...`, or `(nil)` if `NULL`) |
| `%d` / `%i` | a signed decimal integer |
| `%u` | an unsigned decimal integer |
| `%x` | an unsigned integer in lowercase hexadecimal |
| `%X` | an unsigned integer in uppercase hexadecimal |
| `%%` | a literal percent sign |

Flags, width and precision are not handled (mandatory part only).

### Project structure

```
.
├── Makefile
├── ft_printf.h        # prototypes and includes
├── ft_printf.c        # format parsing and dispatch
├── ft_putchar.c       # %c and the base output primitive
├── ft_putstr.c        # %s
├── ft_putnbr.c        # %d / %i
├── ft_putunsnbr.c     # %u
├── ft_puthex.c        # %x / %X
└── ft_putadresse.c    # %p
```

## Instructions

### Compilation

```bash
make        # builds libftprintf.a
make clean  # removes the object files
make fclean # removes the object files and libftprintf.a
make re     # fclean + all
```

The code is compiled with `cc -Wall -Wextra -Werror`.

### Usage

Include the header and link against the library:

```c
#include "ft_printf.h"

int main(void)
{
	int n;

	n = ft_printf("Hello %s, you are %d years old (0x%x)\n", "42", 42, 42);
	ft_printf("Printed %d characters\n", n);
	return (0);
}
```

```bash
cc -Wall -Wextra -Werror main.c -lftprintf -o test
./test
```

## Technical choices

### Algorithm

`ft_printf` walks through the format string **one character at a time**, in a single pass:

1. If the current character is not `%`, it is printed as is with `ft_putchar`.
2. If it is `%`, the next character selects the conversion. A static dispatcher (`ft_check_format`) calls the matching helper and fetches the argument with `va_arg`.
3. Every helper returns the number of characters it wrote, and `ft_printf` accumulates them into the total.
4. If any `write` fails (returns `-1`), the error is propagated back up immediately, `va_end` is called and `ft_printf` returns `-1`.

The number conversions are **recursive**:

- `ft_putnbr` / `ft_putunsnbr` print `nb / 10` first, then the last digit `nb % 10`, so digits come out in the right order without any buffer. `INT_MIN` is handled as a special case, because `-nb` would overflow.
- `ft_puthex` does the same with base 16, using the lookup strings `"0123456789abcdef"` or `"0123456789ABCDEF"` to pick the digit. The value `0` is handled separately so that it prints `0`.
- `ft_putadresse` casts the pointer to `size_t`, counts the number of hexadecimal digits, then fills a `malloc`'d string from the end (`tmp % 16`, `tmp /= 16`). It then prints `0x` followed by the string and frees it. A `NULL` pointer prints `(nil)`.

### Data structures

No custom data structure is needed here, and this was a deliberate choice:

- **`va_list`** is the only structure required: it is the standard way to walk through a variable number of arguments.
- **No output buffer.** Each character is sent with `write` right away. This keeps the code simple, and makes it easy to detect a write error and return the exact count. The trade-off is more system calls than the real `printf`, which buffers its output.
- **No struct for the format specification.** Since only single-letter conversions without flags are required, a chain of `if / else if` in one dispatcher function is enough and easier to read than a table of function pointers.
- **Recursion instead of a temporary array** for numbers: it avoids allocating memory, and the depth is tiny (at most 10 levels for a 32-bit decimal, 8 for hexadecimal). The only allocation is in `%p`, because a pointer can need up to 16 digits, and it is always freed (including on error paths).

## Resources

### References

- ISO C Standard: section 7.23.6
- *Understanding Variable Arguments in C*
- *amd64 and va_arg*, Made of Bugs (blog post)
- RadiatingLight's comment on *Struggling to understand the std lib docs*, r/cprogramming (Reddit)
- [`va_arg` manual page](https://linux.die.net/man/3/va_arg) (also available locally with `man va_arg`)

### Use of AI

AI (Claude) was used **only for learning**, not to write the code of the project:

- **Makefile**: to understand how it works (variables, pattern rules `%.o: %.c`, `$<` and `$@`, `.PHONY`, the compilation steps `make` goes through, and what "relink" means and how to avoid it).
- **README**: to help structure and write this file.

The C source files (`ft_printf.c`, the `ft_put*.c` helpers) were written and tested by me.
