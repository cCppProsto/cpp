#ifndef GPS_TOOL_H
#define GPS_TOOL_H

namespace Navigation
{

// 40.446
struct degreeD
{
    double degree;
    char   ch;
};

// 40° 26.767′
struct degreeDM
{
    double degree;
    double minutes;
    char   ch;
};

// 40° 26′ 46″
struct degreeDMS
{
    double degree;
    double minutes;
    double seconds;
    char ch;
};

namespace constants
{
    constexpr double PI   = 3.141592653589793;
    constexpr double PI_2 = PI / 2.;
    constexpr double PI_4 = PI / 4.;

    constexpr double LatitudeRightRange = 90.0;
    constexpr double LatitudeLeftRange  = -90.0;

    constexpr double LongitudeRightRange = 180.0;
    constexpr double LongitudeLeftRange  = -180.0;

    constexpr double DegreeToRadianCoof = PI / 180.;
    constexpr double RadianToDegreeCoof = 180. / PI;


    constexpr double EarthRadiusM       = 6371001;
    constexpr double EarthRadiusKM      = 6371.001;

    constexpr double RadiusAtEquatorM   = 6378137;
    constexpr double RadiusAtEquatorKM  = 6378.137;

    constexpr double RadiusAtPoleM      = 6356752;
    constexpr double RadiusAtPoleKM     = 6356.752;
}

//----------------------- LATITUDE ---------------------------------------------
struct Latitude
{
    Latitude(double);
    Latitude(const Latitude &other);
    Latitude &operator=(const Latitude &);
    ~Latitude();

    Latitude &operator=(const Latitude &&) = delete;
    Latitude(const Latitude &&)            = delete;

    bool operator==(const Latitude &) const;
    bool operator!=(const Latitude &) const;

    const degreeD &point()const;

private:
    void checkAndCorrect();

private:
    degreeD mPoint;
};
//----------------------- LONGITUDE --------------------------------------------
struct Longitude
{
    Longitude(double);
    Longitude(const Longitude &other);
    Longitude &operator=(const Longitude &);
    ~Longitude();

    Longitude &operator=(const Longitude &&) = delete;
    Longitude(const Longitude &&)            = delete;

    bool operator==(const Longitude &) const;
    bool operator!=(const Longitude &) const;

    const degreeD &point()const;

private:
    void checkAndCorrect();

private:
    degreeD mPoint;
};

struct Point2D
{
    Point2D(double, double);
    Point2D(const Latitude &, const Longitude &);

    Point2D(const Point2D &);
    Point2D &operator=(const Point2D &);

    Point2D &operator=(const Point2D &&) = delete;
    Point2D(const Point2D &&) = delete;

    const Latitude &latitude()const;
    const Longitude &longitude()const;

    bool operator==(const Point2D &) const;
    bool operator!=(const Point2D &) const;

    double distanceTo(const Point2D &) const;
    double azimuthTo(const Point2D &) const;

private:
    Latitude  mLatitude;
    Longitude mLongitude;
};


namespace common
{
    double degreeToRadian(const double &);
    double toRadian(const Latitude &);
    double toRadian(const Longitude &);

    double radianToDegree(const double &);

    bool latitudeIsCorrect(double);
    bool longitudeIsCorrect(double);

    const degreeDM &toDM(const Latitude&) ;
    const degreeDM &toDM(const Longitude&);

    const degreeDMS &toDMS(const Latitude&);
    const degreeDMS &toDMS(const Longitude&);

    /* return minutes from degree */
    double minutes(const double&);
    double minutes(const Latitude&);
    double minutes(const Longitude&);

    /* return seconds from degree */
    double seconds(const double&);
    double seconds(const Latitude&);
    double seconds(const Longitude&);

    /*
     .p1
      \
       \
        \
       p2._______ .p3

      .p1
       \
        \
         .p2
        /
       /
      .p3
    */
    double courseAzimuth(const Point2D&, const Point2D&, const Point2D&);
}

/*
Formula for the calculation Radius

latitude B, radius R, radius at equator r1, radius at pole r2
R = √ [ (r1² * cos(B))² + (r2² * sin(B))² ] / [ (r1 * cos(B))² + (r2 * sin(B))² ]
*/

}
#endif // GPS_TOOL_H
