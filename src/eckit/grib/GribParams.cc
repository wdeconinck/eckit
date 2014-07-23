/*
 * (C) Copyright 1996-2013 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/memory/Factory.h"
#include "eckit/memory/Builder.h"
#include "eckit/types/FloatCompare.h"
#include "eckit/geometry/Point2.h"

#include "eckit/grib/GribParams.h"
#include "eckit/grib/GribAccessor.h"

namespace eckit {
namespace grib {

//------------------------------------------------------------------------------------------------------

GribParams* GribParams::create( GribHandle& gh )
{
	return Factory<GribParams>::instance().get( gh.gridType() ).create(gh);
}

GribParams::GribParams(GribHandle& gh) : g_(gh)
{
	set("gridType",gh.gridType());

	long edition = gh.edition();
	set("GRIB.edition", edition);

	/// @todo temporary until we use a better unique hash that works also with other formats
	set("hash", gh.geographyHash());

	set("GRIB.geographyHash", gh.geographyHash());

	north_ = gh.latitudeOfFirstGridPointInDegrees();
	south_ = gh.latitudeOfLastGridPointInDegrees();
	west_  = gh.longitudeOfFirstGridPointInDegrees();
	east_  = gh.longitudeOfLastGridPointInDegrees();

	// check area
	epsilon_ = (edition_ == 1) ? 1e-3 : 1e-6; // GRIB1 is in mili while GRIB2 is in micro degrees

	ASSERT(north_ > south_);
	ASSERT(north_ < 90.0  || FloatCompare::is_equal(north_,90.0,epsilon_));
	ASSERT(south_ < 90.0  || FloatCompare::is_equal(south_,90.0,epsilon_));
	ASSERT(north_ > -90.0 || FloatCompare::is_equal(north_,-90.0,epsilon_));
	ASSERT(south_ > -90.0 || FloatCompare::is_equal(south_,-90.0,epsilon_));

	eckit::geometry::reduceTo2Pi(west_);
	eckit::geometry::reduceTo2Pi(east_);

	ASSERT(east_ > west_);

	set("area_n", north_ );
	set("area_s", south_ );
	set("area_w", west_  );
	set("area_e", east_  );

	set("nbDataPoints", gh.nbDataPoints() );
}

GribParams::~GribParams()
{
}

//------------------------------------------------------------------------------------------------------

class GribReducedGG : public GribParams {
public:

GribReducedGG( GribHandle& gh ) : GribParams(gh)
{
	set( "GaussN", GribAccessor<long>("numberOfParallelsBetweenAPoleAndTheEquator")(gh.raw()) );

	set( "Nj", GribAccessor<long>("Nj")(gh.raw()) );
}

};

ConcreteBuilderT1<GribParams,GribReducedGG> GribReducedGG_builder;

//------------------------------------------------------------------------------------------------------

class GribRegularGG : public GribParams {
public:

GribRegularGG( GribHandle& gh ) : GribParams(gh)
{
	set( "GaussN", GribAccessor<long>("numberOfParallelsBetweenAPoleAndTheEquator")(gh.raw()) );

	set( "Nj", GribAccessor<long>("Nj")(gh.raw()) );
}

};

ConcreteBuilderT1<GribParams,GribRegularGG> GribRegularGG_builder;

//------------------------------------------------------------------------------------------------------

class GribRegularLatLon : public GribParams {
public:

GribRegularLatLon( GribHandle& gh ) : GribParams(gh)
{
	set( "jInc", GribAccessor<double>("jDirectionIncrementInDegrees")(gh.raw()) );
	set( "iInc", GribAccessor<double>("iDirectionIncrementInDegrees")(gh.raw()) );

	set( "Nj", GribAccessor<long>("Nj")(gh.raw()) );
	set( "Ni", GribAccessor<long>("Ni")(gh.raw()) );
}

};

ConcreteBuilderT1<GribParams,GribRegularLatLon> GribRegularLatLon_builder;

//------------------------------------------------------------------------------------------------------

class GribReducedLatLon : public GribParams {
public:

GribReducedLatLon( GribHandle& gh ) : GribParams(gh)
{
	set( "jInc", GribAccessor<double>("jDirectionIncrementInDegrees")(gh.raw()) );

	set( "Nj", GribAccessor<long>("Nj")(gh.raw()) );
}

};

ConcreteBuilderT1<GribParams,GribReducedLatLon> GribReducedLatLon_builder;

//------------------------------------------------------------------------------------------------------

class GribRotatedLatLon : public GribParams {
public:

GribRotatedLatLon( GribHandle& gh ) : GribParams(gh)
{
	set( "jInc", GribAccessor<double>("jDirectionIncrementInDegrees")(gh.raw()) );
	set( "iInc", GribAccessor<double>("iDirectionIncrementInDegrees")(gh.raw()) );

	set( "Nj", GribAccessor<long>("Nj")(gh.raw()) );
	set( "Ni", GribAccessor<long>("Ni")(gh.raw()) );

	set( "SouthPoleLat", GribAccessor<double>("latitudeOfSouthernPoleInDegrees")(gh.raw()) );
	set( "SouthPoleLon", GribAccessor<double>("longitudeOfSouthernPoleInDegrees")(gh.raw()) );
	set( "SouthPoleRotAngle", GribAccessor<double>("angleOfRotation")(gh.raw()) );
}

};

ConcreteBuilderT1<GribParams,GribRotatedLatLon> GribRotatedLatLon_builder;

//------------------------------------------------------------------------------------------------------

} // namespace grib
} // namespace eckit