#include <cmath>

#include "../math_lib.cxx"
#include "../computational_geometry_lib.cxx"
#include "common_testing_lib.h"

void test_general_functions()
{
	TEST_ASSERT( FLOAT_EQUALS( ( hypotenuse<double, double>( 4.0, 3.0 ) ), 5.0 ), "hypotenuse: Test 1 (4.0, 3.0) == 5.0" );
}

void test_point_t()
{
	point_t<int> test_point_1(2,2);
}

void test_computation_geometry_lib()
{
	test_general_functions();
	test_point_t();
	//test_line_t();
}

int main(int argc, char *argv[])
{
	test_computation_geometry_lib();
	return 0;
}
