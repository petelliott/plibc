/*
implementaton of the c runtime, holds the entry point and executes main
Copyright (C) 2017  Peter Elliott

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

.text

.globl _start

_start: # _start is the entry point known to the linker
    mov %rsp, %rbp    # setup a new stack frame
    mov 0(%rbp), %rdi # get argc from the stack
    mov 8(%rbp), %rsi # get argv from the stack
    call main         # %rdi, %rsi are the first two args to main

    mov %rax, %rdi    # mov the return of main to the first argument
    mov $60, %rax     # set %rax for syscall 60 (exit)
    syscall           # call the kernel to exit
