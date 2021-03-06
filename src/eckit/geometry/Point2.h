#ifndef eckit_geometry_Point2_h
#define eckit_geometry_Point2_h

#include "eckit/geometry/KPoint.h"
#include "eckit/value/Value.h"

//------------------------------------------------------------------------------------------------------

namespace eckit {
namespace geometry {

//------------------------------------------------------------------------------------------------------

class Point2 : public eckit::geometry::KPoint<2> {

    typedef KPoint<2> BasePoint;

public:

    Point2(): BasePoint() {}

    Point2( const BasePoint& p ) : BasePoint(p) {}

    Point2( const double* p ) : BasePoint(p) {}

    Point2( double x, double y ) : BasePoint( NoInit() )
    {
        x_[XX] = x;
        x_[YY] = y;
    }

    double  operator[] (const size_t& i) const { assert(i<2); return x_[i]; }
    double& operator[] (const size_t& i)       { assert(i<2); return x_[i]; }

    template < typename T >
    void assign( const T& p )
    {
        x_[XX] = p[XX];
        x_[YY] = p[YY];
    }

    operator eckit::Value() const;

};

//------------------------------------------------------------------------------------------------------

bool points_equal( const Point2&, const Point2& );

//------------------------------------------------------------------------------------------------------

} // namespace geometry
} // namespace eckit

#endif

