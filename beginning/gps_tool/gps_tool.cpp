#include <cmath>
#include <iostream>

#include "gps_tool.h"

namespace Navigation
{

namespace common
{
    //--------------------------------------------------------------------------
    double degreeToRadian(const double &aDegree)
    {
        return aDegree * constants::DegreeToRadianCoof;
    }
    //--------------------------------------------------------------------------
    double toRadian(const Latitude &aLat)
    {
        return aLat.point().degree * constants::DegreeToRadianCoof;
    }
    //--------------------------------------------------------------------------
    double toRadian(const Longitude &aLong)
    {
        return aLong.point().degree * constants::DegreeToRadianCoof;
    }
    //--------------------------------------------------------------------------
    double radianToDegree(const double &aRadian)
    {
        return aRadian * constants::RadianToDegreeCoof;
    }
    //--------------------------------------------------------------------------
    bool latitudeIsCorrect(double aDegree)
    {
        return    (aDegree >= constants::LatitudeLeftRange)
               && (aDegree <= constants::LatitudeRightRange);
    }
    //--------------------------------------------------------------------------
    bool longitudeIsCorrect(double aDegree)
    {
        return    (aDegree >= constants::LongitudeLeftRange)
               && (aDegree <= constants::LongitudeRightRange);
    }
    //--------------------------------------------------------------------------
    double minutes(const double &aDegree)
    {
        return 60. * (aDegree - (int)aDegree);
    }
    //--------------------------------------------------------------------------
    double minutes(const Latitude &aLat)
    {
        return 60. * (aLat.point().degree - (int)(aLat.point().degree));
    }
    //--------------------------------------------------------------------------
    double minutes(const Longitude &aLon)
    {
        return 60. * (aLon.point().degree - (int)(aLon.point().degree));
    }
    //--------------------------------------------------------------------------
    double seconds(const double &aDegree)
    {
        double minutes = 60. * (aDegree - (int)aDegree);
        return 60. * (minutes - (int)minutes);
    }
    //--------------------------------------------------------------------------
    double seconds(const Latitude &aLat)
    {
        double minutes = 60. * (aLat.point().degree - (int)aLat.point().degree);
        return 60. * (minutes - (int)minutes);
    }
    //--------------------------------------------------------------------------
    double seconds(const Longitude &aLon)
    {
        double minutes = 60. * (aLon.point().degree - (int)aLon.point().degree);
        return 60. * (minutes - (int)minutes);
    }
    //--------------------------------------------------------------------------
    const degreeDM &toDM(const Latitude &aLat)
    {
        static degreeDM res{0.0, 0.0, 'N'};
        res.degree  = std::fabs((int)aLat.point().degree);
        res.minutes = std::fabs(common::minutes(aLat.point().degree));
        res.ch      = aLat.point().ch;
        return res;
    }
    //--------------------------------------------------------------------------
    const degreeDM &toDM(const Longitude &aLong)
    {
        static degreeDM res{0.0, 0.0, 'E'};
        res.degree  = std::fabs((int)aLong.point().degree);
        res.minutes = std::fabs(common::minutes(aLong.point().degree));
        res.ch      = aLong.point().ch;
        return res;
    }
    //--------------------------------------------------------------------------
    const degreeDMS &toDMS(const Latitude &aLat)
    {
        static degreeDMS res{0.0, 0.0, 0.0, 'N'};
        res.degree  = std::fabs((int)aLat.point().degree);
        res.minutes = std::fabs((int)common::minutes(aLat.point().degree));
        res.seconds = std::fabs(common::seconds(aLat.point().degree));
        res.ch      = aLat.point().ch;
        return res;
    }
    //--------------------------------------------------------------------------
    const degreeDMS &toDMS(const Longitude &aLong)
    {
        static degreeDMS res{0.0, 0.0, 0.0, 'E'};
        res.degree  = std::fabs((int)aLong.point().degree);
        res.minutes = std::fabs((int)common::minutes(aLong.point().degree));
        res.seconds = std::fabs(common::seconds(aLong.point().degree));
        res.ch      = aLong.point().ch;
        return res;
    }
    //--------------------------------------------------------------------------
    double courseAzimuth(const Point2D &aP1, const Point2D &aP2, const Point2D &aP3)
    {
        double az1 = aP1.azimuthTo(aP2);
        double az2 = aP2.azimuthTo(aP3);

        if(az1 >= 0.0 && az1 < 90.0)
            return (az2 - 90.0) + (90.0 - az1);
        if(az1 >= 90.0 && az1 < 180.0)
            return (az2 - 180.0) + (180.0 - az1);
        if(az1 >= 180.0 && az1 < 270.0)
            return (az2 - 270.0) + (270.0 - az1);
        if(az1 >= 270.0 && az1 <= 360.0)
            return (az2 - 360.0) + (360.0 - az1);
        return 0.0;
    }
}

//----------------------- LATITUDE ---------------------------------------------
//------------------------------------------------------------------------------
Latitude::Latitude(double aDegree)
    :mPoint{aDegree, 'N'}
{
    checkAndCorrect();
}
//------------------------------------------------------------------------------
Latitude::Latitude(const Latitude &other)
    :mPoint{other.mPoint.degree, other.mPoint.ch}
{
    std::cout << "copy constructor" << std::endl;
}
//------------------------------------------------------------------------------
Latitude &Latitude::operator=(const Latitude &aObj)
{
    if(this == &aObj)
        return *this;
    mPoint.degree = aObj.mPoint.degree;
    mPoint.ch     = aObj.mPoint.ch;

    std::cout << "operator = copy" << std::endl;

    return *this;
}
//------------------------------------------------------------------------------
Latitude::~Latitude()
{
}
//------------------------------------------------------------------------------
bool Latitude::operator==(const Latitude &aRhs) const
{
    return mPoint.degree == aRhs.mPoint.degree;
}
//------------------------------------------------------------------------------
bool Latitude::operator!=(const Latitude &aRhs) const
{
    return !(*this == aRhs);
    //return !(operator ==(aRhs));
}
//------------------------------------------------------------------------------
void Latitude::checkAndCorrect()
{
    if(!common::latitudeIsCorrect(mPoint.degree))
    {
        if(mPoint.degree >= 0.0)
            mPoint.degree = constants::LatitudeRightRange;
        else
            mPoint.degree = constants::LatitudeLeftRange;
    }

    mPoint.ch = (mPoint.degree >= 0.0) ? 'N' : 'S';
}
//------------------------------------------------------------------------------
const degreeD &Latitude::point()const
{
    return mPoint;
}

//----------------------- LONGITUDE --------------------------------------------
//------------------------------------------------------------------------------
Longitude::Longitude(double aDegree)
    :mPoint{aDegree, 'E'}
{
    checkAndCorrect();
}
//------------------------------------------------------------------------------
Longitude::Longitude(const Longitude &other)
    :mPoint{other.mPoint.degree, other.mPoint.ch}
{
}
//------------------------------------------------------------------------------
Longitude &Longitude::operator=(const Longitude &aObj)
{
    if(this == &aObj)
        return *this;
    mPoint.degree = aObj.mPoint.degree;
    mPoint.ch     = aObj.mPoint.ch;
    return *this;
}
//------------------------------------------------------------------------------
Longitude::~Longitude()
{
}
//------------------------------------------------------------------------------
bool Longitude::operator==(const Longitude &aRhs) const
{
    return mPoint.degree == aRhs.mPoint.degree;
}
//------------------------------------------------------------------------------
bool Longitude::operator!=(const Longitude &aRhs) const
{
    return !(*this == aRhs);
    //return !(operator ==(aRhs));
}
//------------------------------------------------------------------------------
void Longitude::checkAndCorrect()
{
    if(!common::longitudeIsCorrect(mPoint.degree))
    {
        if(mPoint.degree >= 0.0)
            mPoint.degree = constants::LongitudeRightRange;
        else
            mPoint.degree = constants::LongitudeLeftRange;
    }

    mPoint.ch = (mPoint.degree >= 0.0) ? 'E' : 'W';
}
//------------------------------------------------------------------------------
const degreeD &Longitude::point()const
{
    return mPoint;
}

//----------------------- POINT ------------------------------------------------
//------------------------------------------------------------------------------
Point2D::Point2D(double aLatitude, double aLongitude)
    :mLatitude(aLatitude)
    ,mLongitude(aLongitude)
{
}
//------------------------------------------------------------------------------
Point2D::Point2D(const Latitude &aLat, const Longitude &aLong)
    :mLatitude(aLat)
    ,mLongitude(aLong)
{
}
//------------------------------------------------------------------------------
Point2D::Point2D(const Point2D &aObj)
    :mLatitude(aObj.mLatitude)
    ,mLongitude(aObj.mLongitude)
{
}
//------------------------------------------------------------------------------
Point2D &Point2D::operator=(const Point2D &aObj)
{
    if(this == &aObj)
        return *this;

    mLatitude  = aObj.mLatitude;
    mLongitude = aObj.mLongitude;

    return *this;
}
//------------------------------------------------------------------------------
const Latitude &Point2D::latitude()const
{
    return mLatitude;
}
//------------------------------------------------------------------------------
const Longitude &Point2D::longitude()const
{
    return mLongitude;
}
//------------------------------------------------------------------------------
bool Point2D::operator==(const Point2D &aRhs) const
{
    return (mLatitude == aRhs.mLatitude) && (mLongitude == aRhs.mLongitude);
}
//------------------------------------------------------------------------------
bool Point2D::operator!=(const Point2D &aRhs) const
{
    return !(operator ==(aRhs));
}
//------------------------------------------------------------------------------
double Point2D::distanceTo(const Point2D &aTarget) const
{
    double a1 = common::toRadian(mLatitude);
    double a2 = common::toRadian(mLongitude);
    double b1 = common::toRadian(aTarget.mLatitude);
    double b2 = common::toRadian(aTarget.mLongitude);

    double t1 = std::cos(a1) * std::cos(a2) * std::cos(b1) * std::cos(b2);
    double t2 = std::cos(a1) * std::sin(a2) * std::cos(b1) * std::sin(b2);
    double t3 = std::sin(a1) * std::sin(b1);
    double tt = std::acos(t1 + t2 + t3);

    return constants::EarthRadiusM * tt;
}
//------------------------------------------------------------------------------
double Point2D::azimuthTo(const Point2D &aTarget) const
{
    double lat1  = common::toRadian(mLatitude);
    double lat2  = common::toRadian(aTarget.mLatitude);
    double long1 = common::toRadian(mLongitude);
    double long2 = common::toRadian(aTarget.mLongitude);

    double cl1      = std::cos(lat1);
    double cl2      = std::cos(lat2);
    double sl1      = std::sin(lat1);
    double sl2      = std::sin(lat2);
    double delta    = long2 - long1;
    double cdelta   = std::cos(delta);
    double sdelta   = std::sin(delta);

    double y    = std::sqrt(std::pow(cl2 * sdelta, 2) +
                            std::pow(cl1 * sl2 - sl1 * cl2 * cdelta, 2));

    double x    = sl1 * sl2 + cl1 * cl2 * cdelta;

    x = (cl1 * sl2) - (sl1 * cl2 * cdelta);
    y = sdelta * cl2;
    double z = ((std::atan(-y/x))*180.0)/constants::PI;

    if (x < 0)
        z = z+180.0;

    double z2 = std::fmod((z+180.0),360.0) - 180.0;

    z2 = -1.0 * ((constants::PI*z2)/180.0);
    double anglerad2 = z2 - ((2*constants::PI)*std::floor((z2/(2*constants::PI))));

    return (anglerad2 * 180.0) / constants::PI;
}

}
