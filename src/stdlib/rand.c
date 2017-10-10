/*
srand and rand
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
#include <stdlib.h>
#include <stdint.h>

// taken from glibc
const unsigned int a = 1103515245;
const unsigned int c = 12345;
const unsigned int mod = (1l<<31) - 1;

unsigned int state = 0;


void srand(unsigned int seed) {
    state = seed;
}


/*
    Linear congruential generator
*/
int rand(void) {
    state = (a * state + c) % mod;
    return state;
}
