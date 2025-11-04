/*
 * Copyright (c) 2022
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys_init.h>
#include <cm4.h>
#include <kmain.h>
#include <stdint.h>
#include <sys_usart.h>
#include <kstdio.h>
#include <sys_rtc.h>
#include <kstring.h>
#include <unistd.h>

#ifndef DEBUG
#define DEBUG 1
#endif
// void kmain(void)
// {
//     __sys_init();
//     kprintf("Group Members:\n");
//     kprintf("1. Md. Al Habib — Roll: 17 — Reg: 2021011193\n");
//     kprintf("2. Md. Rohul Amin — Roll: 27 — Reg: 2021811203\n");
//     kprintf("3. Syed Naimul Islam — Roll: 37 — Reg: 2021711213\n");
//     char buffer[128]; // storage for read input
//     memset(buffer, 0, sizeof(buffer));

//     kprintf("Enter something: ");
//     int n = read(0, buffer, sizeof(buffer)); // call your syscall wrapper

//     if (n > 0)
//     {
//         kprintf("\nYou typed: %s\n", buffer);
//     }
//     else
//     {
//         kprintf("\nRead failed or no input\n");
//     }
//     while (1)
//     {
//     }
// }

extern void user_task(void);

int kmain(void)
{
    __sys_init();
    

    kprintf("If you see X above, UART works\n");
    
    while (1);
}
