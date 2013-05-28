//
// common defines & constants
#define PI 3.14159265359
#define EPSILON 1E-9
#define ANGLE_TO_RADIANS_MULTIPLIER 0.01745329251994 // PI / 180.0;
#define FLOAT_EQUALS( num1, num2 ) ( fabs( num1 - num2 ) < EPSILON )

//
// absolute value
template<typename number_type>
number_type absolute_value( const number_type &number )
{
	if( number < (number_type)0 )
		return -number;
	else 
		return number;
}

template<> double absolute_value( const double &number ) { return fabs( number ); }
template<> float absolute_value( const float &number ) { return fabsf( number ); }

// Greatest common divisor
template< typename number_type >
number_type gcd( number_type number_1, number_type number_2 )
{
	number_type temp;
	while( number_2 != 0 )
	{
		temp = number_1 % number_2;
		number_1 = number_2;
		number_2 = temp;
	}
	return number_1;
}

// Lowest common multiple
template< typename number_type >
number_type lcm( number_type number_1, number_type number_2 )
{
	return ( number_1 * ( number_2 / gcd( number_1, number_2 ) ) );
}

// Simple primality test

// Miller rabin primality test

// Sieve of eratosthenes

// Get first N primes
