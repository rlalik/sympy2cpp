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

#define FOR_MASSIF 1
int main(int argc, char ** argv)
{
	// initialize module
	Sympy2cpp * s2c = new Sympy2cpp("example");

	/* This part of the code is uselfull to track memory leaks.
	 * Produces big bump in massif output for a reference,
	 * where python ends its initialisation.
	 * IGNORE CODE BELOW FOR NORMAL USAGE
	 */
#ifdef FOR_MASSIF
	const size_t size = 1000000;
	for (uint j = 0; j < 10; ++j)
	{
		double * test_arr = new double[size];
		for (uint i = 0; i < size; ++i)
			test_arr[i] = 13.0;
		delete [] test_arr;
	}
#endif /* FOR_MASSIF */

	double a_m[10];
	double a_n[10];
	double b_p[10];
	double b_q[10];
	double z = 2.25;

	// test for exp(z)
	b_p[0] = 0;

	/* Run function in loop to check for memory leaks
	 * in function calls.
	 * IGNORE CODE BELOW FOR NORMAL USAGE
	 */
#ifdef FOR_MASSIF
	const size_t test_loops = 1000;
	for (int i = 0; i < test_loops; ++i)
	{
#endif /* FOR_MASSIF */

		double res = 13.0;
		res = s2c->meijerg(0, 0, 1, 0, a_m, a_n, b_p, b_q, -z);
		printf("exp(2.25) = %g\n", res);


	/* IGNORE CODE BELOW FOR NORMAL USAGE
	 */
#ifdef FOR_MASSIF
	}
#endif /* FOR_MASSIF */

	delete s2c;

	/* Tests for massif to see whether there are memory leaks
	 * after calling constructor multiple times.
	 * For now I observe incerease of memory, don't know
	 * yet why.
	 * But for most of the cases, you need single instance of the
	 * object -> think about making it singleton.
	 * IGNORE CODE BELOW FOR NORMAL USAGE
	 */
#ifdef FOR_MASSIF
	for (int j = 0; j < 10; ++j)
	{
		Sympy2cpp * s2c = new Sympy2cpp("example");
		delete s2c;
	}
#endif /* FOR_MASSIF */

	return 0;
}