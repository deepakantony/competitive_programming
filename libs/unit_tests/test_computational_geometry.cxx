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
	point_t<double> test_double_point_1(2.4, 3.6);
	point_t<double> test_double_point_2(2.5, 3.6);

	point_t<double> test_double_point_4(0.0, 890.98789);

	// Test distance method
	TEST_ASSERT( 
		FLOAT_EQUALS( test_int_point_1.distance<double>( test_int_point_2 ), 1.414213 ),
		"Integer point to double distance" );
	TEST_ASSERT(
		test_int_point_1.distance<int>( test_int_point_2 ) == 1, 
		"Integer point to int distance" );
	TEST_ASSERT(
		point_t<int>(0,0).distance<int>(point_t<int>(3,4)) == 5, 
		"Integer point to int distance" );
	TEST_ASSERT(
		FLOAT_EQUALS( test_double_point_1.distance<double>( test_double_point_2 ), 0.1 ),
		"Double point to double distance" );

	// Test rotation and equals
	test_int_point_1 = point_t<int>(4,0);
	TEST_ASSERT(
		test_int_point_1.rotate_by_angle_in_degrees( 90 ) == point_t<int>(0, 4),
		"Rotate by 90, a point on x axis" );
	test_double_point_1 = point_t<double>(0.789, 0.0);
	TEST_ASSERT(
		test_double_point_1.rotate_by_angle_in_degrees( -90 ) == point_t<double>(0.0, -0.789),
		"Rotate by -90, a point on x axis" );
	test_double_point_1 = point_t<double>(0.0, 890.9898987);
	TEST_ASSERT(
		test_double_point_1.rotate_by_angle_in_degrees( 90 ) == point_t<double>(-890.9898987, 0.0),
		"Rotate by 90, a point on y axis" );
	TEST_ASSERT(
		test_double_point_1.rotate_by_angle_in_degrees( 180 ) == point_t<double>(0.0, -890.9898987),
		"Rotate by 180, a point on y axis" );

	// Test less than
	test_int_point_1 = point_t<int>(4,5);
	test_int_point_2 = point_t<int>(4,6);
	TEST_ASSERT( test_int_point_1 < test_int_point_2, "Less than for int" );
	test_double_point_1 = point_t<double>(4.5, 7.4);
	test_double_point_2 = point_t<double>(5.4, 8.999);
	TEST_ASSERT( test_double_point_1 < test_double_point_2, "Less than for double" );
}

void test_class_line_t()
{
	line_t test_line_1( point_t<int>(2,2), point_t<int>(4,2) );
	line_t test_line_2( point_t<int>(4,0), point_t<int>(2,0) );
	line_t test_line_3( point_t<int>(0,2), point_t<int>(0,4) );
	line_t same_line_as_1( point_t<int>(2,2), point_t<int>(4,2) );
	line_t x_axis( 0.0, 0.0 );
	line_t y_axis( point_t<int>(0, 0), point_t<int>(0, 1) );

	// Test parallel lines
	TEST_ASSERT( test_line_1.is_parallel( x_axis ), "Parallel with xaxis" );
	TEST_ASSERT( test_line_3.is_parallel( y_axis ), "Parallel with yaxis" );
	TEST_ASSERT( test_line_1.is_parallel( test_line_2 ), "Parallel with another line" );
	TEST_ASSERT( !test_line_1.is_parallel( y_axis ), "NOT parallel with yaxis" );

	// Test same lines
	TEST_ASSERT( test_line_1.is_same( same_line_as_1 ), "Test with same line" );
	TEST_ASSERT( !test_line_1.is_same( x_axis ), "Test with not same line" );

	// Test intersection of lines
	point_t<double> intersection_pt;
	TEST_ASSERT( test_line_1.get_intersection_point( y_axis, intersection_pt ), 
				 "Test intersection point true return result" );
	TEST_ASSERT( intersection_pt == point_t<double>( 0.0, 2.0 ), 
				 "Test intersection point" );
	TEST_ASSERT( !test_line_1.get_intersection_point( x_axis, intersection_pt ), 
				 "Test intersection point false return result" );

}

void test_computation_geometry_lib()
{
	test_general_functions();
	test_class_point_t();
	test_class_line_t();
}

int main(int argc, char *argv[])
{
	test_computation_geometry_lib();
	return 0;
}
