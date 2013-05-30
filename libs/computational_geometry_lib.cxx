//
// hypotenuse
template<typename length_type, typename return_type>
return_type hypotenuse(const length_type side_a, const length_type side_b)
{
	return return_type( sqrt( side_a * side_a + side_b * side_b ) );
}

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
		if( x_ == other_point.x_ ) return y_ < other_point.y_;
		else return x_ < other_point.x_;
	}

	bool operator== (const point_t<coordinate_type> &other_point) const {
		return (x_ == other_point.x_) && (y_ == other_point.y_);
	}

private:
	coordinate_type x_, y_;
};

template<> bool point_t<double>::operator< (const point_t<double> &other_point) const
{
	if( FLOAT_EQUALS( x_, other_point.x_ ) )
		return y_ < other_point.y_;
	else
		return x_ < other_point.x_;
}
template<> bool point_t<float>::operator< (const point_t<float> &other_point) const
{
	if( FLOAT_EQUALS( x_, other_point.x_ ) )
		return y_ < other_point.y_;
	else
		return x_ < other_point.x_;
}
template<> bool point_t<double>::operator== (const point_t<double> &other_point) const
{
	return ( FLOAT_EQUALS( x_, other_point.x_ ) ) && ( FLOAT_EQUALS( y_, other_point.y_ ) );
}
template<> bool point_t<float>::operator== (const point_t<float> &other_point) const
{
	return ( FLOAT_EQUALS( x_, other_point.x_ ) ) && ( FLOAT_EQUALS( y_, other_point.y_ ) );
}
