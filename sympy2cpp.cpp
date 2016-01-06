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

#include <cstdlib>
#include <iostream>
#include <exception>

#include "sympy2cpp.h"

Sympy2cpp::Sympy2cpp(const char* name) : pName(0), pModule(0), pDict(0),
pFunc_meijerg(0)
{
// 	Py_SetProgramName(name);  /* optional but recommended */
	Py_Initialize();

	// load sympy
	pName = PyUnicode_FromString("sympy.mpmath");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (!pModule)
	{
		PyErr_Print();
		std::cerr << "No Sympy available. Exiting..." << std::endl;
		std::abort();
	}

	// get interafce for meijerg
	pFunc_meijerg = PyObject_GetAttrString(pModule, "meijerg");
	Py_DECREF(pModule);

	if (!(pFunc_meijerg && PyCallable_Check(pFunc_meijerg)))
	{
		Py_XDECREF(pFunc_meijerg);
		PyErr_Print();
		std::abort();
	}
}

Sympy2cpp::~Sympy2cpp()
{
	Py_XDECREF(pFunc_meijerg);
	Py_Finalize();
}

void Sympy2cpp::fill_tuple(PyObject * pO, const size_t size, double * array)
{
	PyObject * pValue;
	for (uint i = 0; i < size; ++i)
	{
		pValue = PyFloat_FromDouble(array[i]);
		PyTuple_SetItem(pO, i, pValue);
	}
}

/* For details please refer to
 * http://docs.sympy.org/0.6.7/modules/mpmath/functions/hypergeometric.html?highlight=meijer#mpmath.meijerg
 *
 * meijerg function in python takes two tuples of tuples
 * as arguments:
 *   a_s = [ [], [] ]
 *   b_s = [ [], [] ],
 * Python can find lengths of all the tuples easily, but in C/C++
 * it is not always possible.
 *
 * In this code, we use following arrays as repalcement for tuples
 *  { a_m, a_n }
 *  { b_p, b_q }
 * where a_m and a_n are subtuples of a_s,
 * and b_p and b_q of b_s accordingly.
 *
 * We should give explicitely lengths to the function
 *  m is length of the first tuple in a_s -> here it is a_m
 *  n is length of the second tuple in a_s -> here it is a_n
 *  p is length of the first tuple in b_s -> here it is b_p
 *  q is length of the second tuple in b_s -> here it is b_q
 *
 * Be aware that m, n, p, q in C++ code are not the same like
 * in Python code, they are redefined in following way
 * (capital letters denote Python variables)
 *  m := M
 *  n := P-M
 *  p := N
 *  q := Q-N
 *
 * z and r are the same like in python example.
 */
double Sympy2cpp::meijerg(int m, int n, int p, int q, double *a_m, double *a_n, double *b_p, double *b_q, double z, double r)
{
	// input tuples
	PyObject * t_a_m = PyTuple_New(m);
	PyObject * t_a_n = PyTuple_New(n);
	PyObject * t_b_p = PyTuple_New(p);
	PyObject * t_b_q = PyTuple_New(q);

	fill_tuple(t_a_m, m, a_m);
	fill_tuple(t_a_n, n, a_n);
	fill_tuple(t_b_p, p, b_p);
	fill_tuple(t_b_q, q, b_q);

	// row tuples
	PyObject * t_a = PyTuple_New(2);
	PyObject * t_b = PyTuple_New(2);

	PyTuple_SetItem(t_a, 0, t_a_m);
	PyTuple_SetItem(t_a, 1, t_a_n);
	PyTuple_SetItem(t_b, 0, t_b_p);
	PyTuple_SetItem(t_b, 1, t_b_q);

	PyObject * pValue = 0;
	PyObject * pArgs = PyTuple_New(4);

	PyTuple_SetItem(pArgs, 0, t_a);
	PyTuple_SetItem(pArgs, 1, t_b);

	// set z
	pValue = PyFloat_FromDouble(z);
	PyTuple_SetItem(pArgs, 2, pValue);

	// set r
	pValue = PyFloat_FromDouble(r);
	PyTuple_SetItem(pArgs, 3, pValue);

	// call function
	pValue = PyObject_CallObject(pFunc_meijerg, pArgs);
	Py_DECREF(pArgs);

	double res = 0.0;

	if (pValue != 0)
	{
		res = PyFloat_AsDouble(pValue);
		Py_DECREF(pValue);
	}
	else
	{
		throw std::bad_exception();
	}

	return res;
}