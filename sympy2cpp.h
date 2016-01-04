/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  Rafał Lalik <rafal.lalik@ph.tum.de>
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

#ifndef SYMPY2CPP_H
#define SYMPY2CPP_H

#include <python3.4/Python.h>

#define PR(x) std::cout << "++DEBUG: " << #x << " = |" << x << "| (" << __FILE__ << ", " << __LINE__ << ")\n";

class Sympy2cpp
{
public:
	Sympy2cpp(const char * name = "sympy2cpp");
	virtual ~Sympy2cpp();

	double meijerg(int m, int n, int p, int q, double *a_m, double *a_n, double *b_p, double *b_q, double z, double r = 1.0);

protected:
	void fill_tuple(PyObject * pO, const size_t size, double * array);

protected:
	PyObject *pName, *pModule, *pDict;
	PyObject *pFunc_meijerg;
};

#endif // SYMPY2CPP_H
