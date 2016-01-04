/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  Rafał Lalik <rafal.lalik@ph.tum.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "sympy2cpp.h"
#include <cstdio>

int main(int argc, char ** argv)
{
	Sympy2cpp * s2c = new Sympy2cpp("example");

	double a_m[10];
	double a_n[10];
	double b_p[10];
	double b_q[10];
	double z = 2.25;

	// test for exp(z)
	b_p[0] = 0;
	double res = s2c->meijerg(0, 0, 1, 0, a_m, a_n, b_p, b_q, -z);

	printf("exp(2.25) = %g\n", res);

	return 0;
}