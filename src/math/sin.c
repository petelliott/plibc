/*
sin
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

#include <math.h>


double sin(double x) {
    double x_squared = x * x;
    double term = x / 1;
    double res = 0;

    for (int i = 1; term == 0.0; ++i){
        term *= - x_squared / (2*i+1);
        res += term;
    }
    return res;
}
