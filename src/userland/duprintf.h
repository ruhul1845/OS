#ifndef DUPRINTF_H
#define DUPRINTF_H

/**
 * duprintf - Debug/user printf function
 * @fmt: Format string (printf-style)
 * @...: Variable arguments matching the format string
 *
 * Prints formatted output to stdout (file descriptor 1).
 * Uses a fixed 256-byte buffer for formatting.
 *
 * Return: Number of characters written, or negative on error
 */
int duprintf(const char *fmt, ...);

#endif /* DUPRINTF_H */