#include <cmath>

#include "../math_lib.cxx"
#include "../computational_geometry_lib.cxx"
#include "common_testing_lib.h"

void test_function_hypotenuse()
{
	TEST_ASSERT( 
		FLOAT_EQUALS( ( hypotenuse<double, int>( 4.0, 3.0 ) ), 5 ), 
					  "Double and int" );

	TEST_ASSERT( 
		FLOAT_EQUALS( ( hypotenuse<double, double>( 1.4567, 45.6504 ) ), 45.673636 ), 
		"Double and double" );

	TEST_ASSERT( 
		FLOAT_EQUALS( ( hypotenuse<double, double>( -1.4567, -45.6504 ) ), 45.673636 ), 
		"Negative inputs" );

	TEST_ASSERT( 
		FLOAT_EQUALS( ( hypotenuse<double, int>( -1.4567, -45.6504 ) ), 45 ), 
		"Negative inputs with int" );
}

void test_general_functions()
{
	test_function_hypotenuse();
}

void test_class_point_t()
{
	point_t<int> test_int_point_1(2,2);
	point_t<int> test_int_point_2(3,3);

	TEST_ASSERT( 
		FLOAT_EQUALS( test_int_point_1.distance<double>( test_int_point_2 ), 1.414213 ),
		"Integer point to double distance" );
	TEST_ASSERT(
		test_int_point_1.distance<int>( test_int_point_2 ) == 1, "Integer point to int distance" );
	TEST_ASSERT(
		point_t<int>(0,0).distance<int>(point_t<int>(3,4)) == 5, "Integer point to int distance" );


}

void test_computation_geometry_lib()
{
	test_general_functions();
	test_class_point_t();
}

int main(int argc, char *argv[])
{
	test_computation_geometry_lib();
	return 0;
}
