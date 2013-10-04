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
	point_t(const coordinate_type &x, const coordinate_type &y) { x_[0] = x, x_[1] = y; }

	template<typename distance_type>
	distance_type distance(const point_t &other_point) const {
		return hypotenuse<coordinate_type, distance_type>( 
			absolute_value( other_point.x_[0] - x_[0] ),
			absolute_value( other_point.x_[1] - x_[1] ) );
	}

	point_t<coordinate_type> rotate_by_angle_in_degrees( double angle_in_degrees ) {
		double angle_in_radians = angle_in_degrees * ANGLE_TO_RADIANS_MULTIPLIER;
		return point_t( 
			x_[0] * cos( angle_in_radians ) - x_[1] * sin( angle_in_radians ),
			x_[0] * sin( angle_in_radians ) + x_[1] * cos( angle_in_radians )
			);
	}

	bool operator< (const point_t<coordinate_type> &other_point) const {
		if( equals( x_[0], other_point.x_[0] ) ) return x_[1] < other_point.x_[1];
		else return x_[0] < other_point.x_[0];
	}

	bool operator== (const point_t<coordinate_type> &other_point) const {
		return ( equals( x_[0], other_point.x_[0] ) ) && ( equals(x_[1], other_point.x_[1] ) );
	}

	coordinate_type x() { return x_[0]; }
	coordinate_type y() { return x_[1]; }

private:
	coordinate_type x_[2]; // TODO: Update this to a template param
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
		if( equals( point_1.x(), point_2.x() ) ) 
		{
			a_ = 1.0;
			b_ = 0.0;
			c_ = -point_1.x();
		}
		else
		{
			a_ = (double)( point_2.y() - point_1.y() );
			c_ = (double)( point_2.x() * point_1.y() - point_1.x() * point_2.y() );
			a_ = -a_ / (double)( point_2.x() - point_2.y() );
			b_ = 1.0;
			c_ = -c_ / (double)( point_2.x() - point_2.y() );
		}
	}

	// slope intercept formula
	// - will not work for vertical lines; what is m?
	line_t( double m, double c ) : a_(-m), b_(1.0), c_(-c) {}

	// is parallel with another line
	bool is_parallel( const line_t &other ) const {
		return ( equals( a_, other.a_ ) && equals( b_, other.b_ ) );
	}

	// is same as another line
	bool is_same( const line_t &other ) const {
		return ( this->is_parallel( other ) && equals( c_, other.c_ ) );
	}
	bool operator==( const line_t &other ) const { return is_same(other); }

	// where does it intersect
	template<typename coordinate_type>
	bool get_intersection_point( const line_t &other, point_t<coordinate_type> &intersection_pt ) const {
		if( this->is_parallel( other ) ) return false;

		coordinate_type x = ( coordinate_type )
			( other.b_ * c_ - b_ * other.c_ ) / ( other.a_ * b_ - a_ * other.b_ );
		coordinate_type y;

		// vertical line
		if( !equals( b_, 0.0 ) ) y = (coordinate_type)(-( a_ * x + c_ ));
		else y = (coordinate_type)(-( other.a_ * x + other.c_ ));

		intersection_pt = point_t<coordinate_type>(x,y);
		return true;
	}
private:
	double a_, b_, c_;
};

class vector_t
{
public:
	vector_t( double x1, double x2 ) { x_[0] = x1, x_[1] = x2; }
	template<typename coordinate_type>
	vector_t( const point_t<coordinate_type> &p1, const point_t<coordinate_type> &p2 ) {
		x_[0] = (double) ( p2.x() - p1.x() );
		x_[1] = (double) ( p2.y() - p2.y() );
	}

	void normalize() { double norm = get_norm(); x_[0] /= norm; x_[1] /= norm; }

	double get_norm_square() const { return (x_[0] * x_[0] + x_[1] * x_[1]); } 

	double get_norm() const { return sqrt(get_norm_square()); }

	template<typename coordinate_type>
	point_t<coordinate_type> translate_point( point_t<coordinate_type> pt ) const { 
		return point_t<coordinate_type>( (coordinate_type)( x_[0] + pt.x() ), coordinate_type( x_[1] + pt.y() ) );
	}

	void scale( double scale_factor ) { x_[0] *= scale_factor; x_[1] *= scale_factor; }

	double dot_product( const vector_t &other ) const { return x_[0] * other.x_[0] + x_[1] * other.x_[1]; }

private:
	double x_[2];
};

// distance from a point
template<typename coordinate_type>
double get_distance_from_a_point( 
	const point_t<coordinate_type> &line_pt1, const point_t<coordinate_type> &line_pt2,
	const point_t<coordinate_type> &pt, point_t<coordinate_type> *p_nearest_pt = NULL ) 
{
	double dist = 0.0;
	vector_t A( line_pt1, line_pt2 ), B( line_pt1, pt );
	double AdotB = A.dot_product( B );
	double distanceToNearestPt = AdotB/B.get_norm();
	vector_t C( B ); C.scale(distanceToNearestPt);
	point_t<coordinate_type> nearest_pt = C.translate_point( line_pt1 );
	dist = nearest_pt.distance( pt );

	if( p_nearest_pt != NULL ) { *p_nearest_pt = nearest_pt; }
	return dist;
}

