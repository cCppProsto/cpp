#include <iostream>
#include <iomanip>
using namespace std;

#include "gps_tool.h"

int main()
{
    {
        // kongo track 1
        Navigation::TrackPoints2D track;
        track.add(Navigation::Point2D{1.920630003579382, 21.74248461586047});
        track.add(Navigation::Point2D(1.913610815102465, 21.74465362512891));
        track.add(Navigation::Point2D(1.908505267385842, 21.7506346949476));
        track.add(Navigation::Point2D(1.905516628714283, 21.74896463498968));
        track.add(Navigation::Point2D(1.89963567113732,  21.75192577989585));
        track.add(Navigation::Point2D(1.90521996987872,  21.7550747097007));
        track.add(Navigation::Point2D(1.909215763218152, 21.75967345468001));
        track.add(Navigation::Point2D(1.929661556669236, 21.77661686695637));
        track.add(Navigation::Point2D(1.928371328894066, 21.77933600521952));
        cout << track.distance() << endl;
        cout << track.num_of_points() << endl;

        Navigation::TrackPoints2D track1(track);
        Navigation::TrackPoints2D track2;
        track2 = track1;

        cout << track1.distance() << endl;
        cout << track1.num_of_points() << endl;

        cout << track2.distance() << endl;
        cout << track2.num_of_points() << endl;
        cout << endl;
    }

    // input - output
    {

    }


    {
        Navigation::Point2D p1(52.31331593397524, 13.90078520263749);
        Navigation::Point2D p2(52.32075379202971, 13.90269916750066);
        Navigation::Point2D p3(52.32153155534778, 13.90419246671976);
        //cout << Navigation::common::courseAzimuth(p1, p2, p3) << endl;
        //cout << p1.azimuthTo(p2) << endl;
        //cout << p2.azimuthTo(p1) << endl;
        //cout << p1.distanceTo(p2) << endl;
    }

    {
        // UP
        cout  << endl << endl;
        Navigation::Point2D p1(38.42259741266339, -97.73089920682205);
        Navigation::Point2D p2(38.44709087503981, -97.72585038666063);

        cout << p1.azimuthTo(p2) << endl;
    }

    {
        // RIGHT
        cout  << endl << endl;
        Navigation::Point2D p1(38.44251655164755, -97.74971375108937);
        Navigation::Point2D p2(38.44072691984572, -97.73599331953108);

        cout << p1.azimuthTo(p2) << endl;
    }

    {
        // DOWN
        cout  << endl << endl;
        Navigation::Point2D p1(38.44251655164755, -97.74971375108937);
        Navigation::Point2D p2(38.43381950295015, -97.75138495051579);

        cout << p1.azimuthTo(p2) << endl;
    }

    {
        // LEFT
        cout  << endl << endl;
        Navigation::Point2D p1(38.44251655164755, -97.74971375108937);
        Navigation::Point2D p2(38.44314063747864, -97.7548632933127);

        cout << p1.azimuthTo(p2) << endl;
    }



    return 0;
}
