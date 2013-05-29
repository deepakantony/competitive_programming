#include <cmath>
#include "../math_lib.cxx"
#include "common_testing_lib.h"

void test_math_lib()
{
	TEST_ASSERT( absolute_value<int>(0) == 0, "Test zero" );
	TEST_ASSERT( absolute_value<int>(100) == 100, "Test positive number" );
	TEST_ASSERT( absolute_value<int>(-200) == 200, "Test negative number" );

	TEST_ASSERT( FLOAT_EQUALS( absolute_value<double>(0.0), 0.0 ), "Test zero" );
	TEST_ASSERT( FLOAT_EQUALS( absolute_value<double>(1000000.768), 1000000.768 ), "Test positive number" );
	TEST_ASSERT( FLOAT_EQUALS( absolute_value<double>(-200.18567), 200.18567 ), "Test negative number" );

	TEST_ASSERT( FLOAT_EQUALS( absolute_value<float>(0.0f), 0.0f ), "Test zero" );
	TEST_ASSERT( FLOAT_EQUALS( absolute_value<float>(10000000.768f), 10000000.768f ), "Test positive number" );
	TEST_ASSERT( FLOAT_EQUALS( absolute_value<float>(-2000.18f), 2000.18f ), "Test negative number" );
}

int main(int argc, char *argv[])
{
	test_math_lib();
	return 0;
}

