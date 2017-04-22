#include <iostream>
#include <iomanip>
using namespace std;

#include "gps_tool.h"

int main()
{
    Navigation::Point2D p1(52.31331593397524, 13.90078520263749);
    Navigation::Point2D p2(52.32075379202971, 13.90269916750066);
    Navigation::Point2D p3(52.32153155534778, 13.90419246671976);

    cout << Navigation::common::courseAzimuth(p1, p2, p3) << endl;

    cout << p1.azimuthTo(p2) << endl;

    cout << p2.azimuthTo(p1) << endl;

    cout << p1.distanceTo(p2) << endl;

    return 0;
}
