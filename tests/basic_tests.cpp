#include <cppunit/extensions/HelperMacros.h>
#include <sympy2cpp.h>
#include <cmath>

class BasicCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( BasicCase );
	CPPUNIT_TEST( MyTest );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();

protected:
	void MyTest();

	Sympy2cpp * s2c;
};

CPPUNIT_TEST_SUITE_REGISTRATION( BasicCase );

void BasicCase::setUp()
{
	s2c = new Sympy2cpp("tests");
}

void BasicCase::MyTest()
{
	double res;

// 	see http://docs.sympy.org/0.6.7/modules/mpmath/functions/hypergeometric.html?highlight=meijer#mpmath.meijerg
// 	for details

	double a_m[10];
	double a_n[10];
	double b_p[10];
	double b_q[10];
	double z = 2.25;

	// test for exp(z)
	b_p[0] = 0;
	res = s2c->meijerg(0, 0, 1, 0, a_m, a_n, b_p, b_q, -z);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( res, exp(z), 0.0001 );

	// test for log(1+z)
	a_m[0] = 1;
	a_m[1] = 1;
	b_p[0] = 1;
	b_q[0] = 0;
	res = s2c->meijerg(2, 0, 1, 1, a_m, a_n, b_p, b_q, z);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( res, log(1+z), 0.0001 );

	// test for rational z/(1+z)
	a_m[0] = 1;
	a_m[1] = 1;
	b_p[0] = 1;
	b_q[0] = 1;
	res = s2c->meijerg(2, 0, 1, 1, a_m, a_n, b_p, b_q, z);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( res, z/(1+z), 0.0001 );

	// test for sinus sin(z)
	b_p[0] = 0.5;
	b_q[0] = 0;
	res = s2c->meijerg(0, 0, 1, 1, a_m, a_n, b_p, b_q, z*z/4);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( res, sin(z)/sqrt(M_PI), 0.0001 );

	// test for cosinus cos(z)
	b_p[0] = 0;
	b_q[0] = 0.5;
	res = s2c->meijerg(0, 0, 1, 1, a_m, a_n, b_p, b_q, z*z/4);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( res, cos(z)/sqrt(M_PI), 0.0001 );

// 	FIXME I am lazy to do rest of the tests...
}
