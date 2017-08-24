/*
the _plibc_syscall function that makes syscalls available in c
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

.globl _plibc_syscall


_plibc_syscall:
    mov %rdi, %rax  # syscall_num
    mov %rsi, %rdi  # syscall arg 0
    mov %rdx, %rsi  # syscall arg 1
    mov %rcx, %rdx  # syscall arg 2
    mov %r8, %r10   # syscall arg 3
    mov %r9, %r8    # syscall arg 4
    mov (%rsp), %r9 # syscall arg 5
    syscall         # make the syscall
