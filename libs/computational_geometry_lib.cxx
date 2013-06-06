//
// hypotenuse
template<typename length_type, typename return_type>
return_type hypotenuse(const length_type side_a, const length_type side_b)
{
	return return_type( sqrt( side_a * side_a + side_b * side_b ) );
}

// Forward declarations
template< typename coordinate_type > class point_t;
class line_t;
class vector_t;
class line_segment_t;
class circle_t;
class quadrilateral_t;
class polygon_t;

//
// Point class
template<typename coordinate_type>
class point_t
{
public:
	point_t() {}
	point_t(const coordinate_type &x, const coordinate_type &y) : x_(x), y_(y) {}

	template<typename distance_type>
	distance_type distance(const point_t &other_point) const {
		return hypotenuse<coordinate_type, distance_type>( 
			absolute_value( other_point.x_ - x_ ),
			absolute_value( other_point.y_ - y_ ) );
	}

	point_t<coordinate_type> rotate_by_angle_in_degrees( double angle_in_degrees ) {
		double angle_in_radians = angle_in_degrees * ANGLE_TO_RADIANS_MULTIPLIER;
		return point_t( 
			x_ * cos( angle_in_radians ) - y_ * sin( angle_in_radians ),
			x_ * sin( angle_in_radians ) + y_ * cos( angle_in_radians )
			);
	}

	bool operator< (const point_t<coordinate_type> &other_point) const {
		if( equals( x_, other_point.x_ ) ) return y_ < other_point.y_;
		else return x_ < other_point.x_;
	}

	bool operator== (const point_t<coordinate_type> &other_point) const {
		return ( equals( x_, other_point.x_ ) ) && ( equals(y_, other_point.y_ ) );
	}

	coordinate_type x() { return x_; }
	coordinate_type y() { return y_; }

private:
	coordinate_type x_, y_;
};

//
// Line class
class line_t
{
public:
	line_t() : a_(0.0), b_(0.0), c_(0.0) {}

	// direct coefficients
	line_t( double a, double b, double c ) : a_(a), b_(b), c_(c) {}

	// two point formula
	template<typename coordinate_type>
	line_t( point_t<coordinate_type> point_1,
			point_t<coordinate_type> point_2 
		) {
		a_ = (double)( point_2.y() - point_1.y() );
		c_ = (double)( point_2.x() * point_1.y() - point_1.x() * point_2.y() );
		if( equals( point_1.x(), point_2.x() ) ) 
			b_ = 0.0;
		else
		{
			a_ = -a_ / (double)( point_2.x() - point_2.y() );
			b_ = 1.0;
			c_ = -c_ / (double)( point_2.x() - point_2.y() );
		}
	}

	// slope intercept formula
	line_t( double m, double c ) : a_(-m), b_(1.0), c_(-c) {}

	// is parallel with another line
	bool is_parallel( const line_t &other ) {
		return ( equals( a_, other.a_ ) && equals( b_, other.b_ ) );
	}

private:
	double a_, b_, c_;
};

