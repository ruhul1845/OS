#include <unistd.h>
#include <syscall_def.h>

int write(int fd, const void *buf, int size)
{
    register int r0 __asm__("r0") = fd;
    register const void *r1 __asm__("r1") = buf;
    register int r2 __asm__("r2") = size;
    register int result;

    __asm__ volatile(
        "svc #55"      // SYS_write = 55
        : "=r"(result)
        : "r"(r0), "r"(r1), "r"(r2)
        : "memory"
    );
    
    return result;
}

int read(int fd, void *buf, int size)
{
    register int r0 __asm__("r0") = fd;
    register void *r1 __asm__("r1") = buf;
    register int r2 __asm__("r2") = size;
    register int result;

    __asm__ volatile(
        "svc #2"      // SYS_read = 2
        : "=r"(result)
        : "r"(r0), "r"(r1), "r"(r2)
        : "memory"
    );
    
    return result;
}

// pid_t getpid(void)
// {
//     register int result;
    
//     __asm__ volatile(
//         "svc #3"      // SYS_getpid = 3
//         : "=r"(result)
//         :
//         : "memory"
//     );
    
//     return result;
// }

void _exit(int status)
{
    register int r0 __asm__("r0") = status;
    
    __asm__ volatile(
        "svc #4"      // SYS__exit = 4
        :
        : "r"(r0)
        : "memory"
    );
    
    while(1);  // Should never return
}

void yield(void)
{
    __asm__ volatile(
        "svc #5"      // SYS_yield = 5
        :
        :
        : "memory"
    );
}