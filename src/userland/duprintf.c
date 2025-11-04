#include <stdarg.h>
#include <unistd.h>
#include "duprintf.h"

// Helper function to convert integer to string
static int int_to_str(int value, char *buf, int base, int is_signed)
{
    char tmp[32];
    int i = 0;
    unsigned int num;
    int is_negative = 0;

    if (is_signed && value < 0) {
        is_negative = 1;
        num = -value;
    } else {
        num = (unsigned int)value;
    }

    // Handle zero case
    if (num == 0) {
        tmp[i++] = '0';
    }

    // Convert to string (reversed)
    while (num != 0) {
        int rem = num % base;
        tmp[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // Add negative sign
    if (is_negative) {
        tmp[i++] = '-';
    }

    // Reverse the string
    int len = i;
    for (int j = 0; j < len; j++) {
        buf[j] = tmp[len - 1 - j];
    }

    return len;
}

// Helper function to convert unsigned to string
static int uint_to_str(unsigned int value, char *buf, int base, int uppercase)
{
    char tmp[32];
    int i = 0;

    // Handle zero case
    if (value == 0) {
        buf[0] = '0';
        return 1;
    }

    // Convert to string (reversed)
    while (value != 0) {
        int rem = value % base;
        if (rem > 9) {
            tmp[i++] = uppercase ? (rem - 10) + 'A' : (rem - 10) + 'a';
        } else {
            tmp[i++] = rem + '0';
        }
        value = value / base;
    }

    // Reverse the string
    int len = i;
    for (int j = 0; j < len; j++) {
        buf[j] = tmp[len - 1 - j];
    }

    return len;
}

int duprintf(const char *fmt, ...)
{
    char buf[256] = {0}; // clear buffer

    int buf_idx = 0;
    va_list args;
    
    va_start(args, fmt);
    
    for (int i = 0; fmt[i] != '\0' && buf_idx < sizeof(buf) - 1; i++) {
        if (fmt[i] == '%') {
            i++; // Move to format specifier
            
            switch (fmt[i]) {
                case 'd':  // Signed decimal integer
                case 'i': {
                    int val = va_arg(args, int);
                    buf_idx += int_to_str(val, &buf[buf_idx], 10, 1);
                    break;
                }
                
                case 'u': { // Unsigned decimal integer
                    unsigned int val = va_arg(args, unsigned int);
                    buf_idx += uint_to_str(val, &buf[buf_idx], 10, 0);
                    break;
                }
                
                case 'x': { // Unsigned hexadecimal (lowercase)
                    unsigned int val = va_arg(args, unsigned int);
                    buf_idx += uint_to_str(val, &buf[buf_idx], 16, 0);
                    break;
                }
                
                case 'X': { // Unsigned hexadecimal (uppercase)
                    unsigned int val = va_arg(args, unsigned int);
                    buf_idx += uint_to_str(val, &buf[buf_idx], 16, 1);
                    break;
                }
                
                case 'p': { // Pointer address
                    buf[buf_idx++] = '0';
                    buf[buf_idx++] = 'x';
                    unsigned int val = (unsigned int)va_arg(args, void*);
                    buf_idx += uint_to_str(val, &buf[buf_idx], 16, 0);
                    break;
                }
                
                case 'c': { // Character
                    char c = (char)va_arg(args, int);
                    buf[buf_idx++] = c;
                    break;
                }
                
                case 's': { // String
                    char *str = va_arg(args, char*);
                    if (str == 0) {
                        str = "(null)";
                    }
                    while (*str && buf_idx < sizeof(buf) - 1) {
                        buf[buf_idx++] = *str++;
                    }
                    break;
                }
                
                case '%': { // Literal %
                    buf[buf_idx++] = '%';
                    break;
                }
                
                default:
                    // Unknown format, just copy it
                    buf[buf_idx++] = '%';
                    buf[buf_idx++] = fmt[i];
                    break;
            }
        } else {
            buf[buf_idx++] = fmt[i];
        }
    }
    
    va_end(args);
    
    // Write to stdout (file descriptor 1)
    if (buf_idx > 0) {
        buf[buf_idx] = '\0';   
        write(1, buf, buf_idx + 1);   

    }
    
    return buf_idx;
}