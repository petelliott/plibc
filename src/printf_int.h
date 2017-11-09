/*
definitions of shared printf functions
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
#ifndef PRINTF_INT_H
#define PRINTF_INT_H

void fn_printf(void (*_wch)(char), const char *fmt, ...);

void fn_prnt_long(void (*_wch)(char), long l);
void fn_prnt_str(void (*_wch)(char), const char *str);
void fn_prnt_char(void (*_wch)(char), char c);

#endif
