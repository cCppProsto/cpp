#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "gps_tool.h"

void foo_a()
{
    {
        Navigation::TrackPoints2D track =
        {
            {1.1, 1.1}
           ,{2.1, 2.1}
           ,{3.1, 3.1}
        };
        int a = 0;
        a ++;
    }

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

void foo_b()
{
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
}

//------------------------------------------------------------------------------
struct sPoint2DRead
{
    double altitude;
    double longitude;
    string description;
};

ifstream &operator >>(ifstream &aFile, sPoint2DRead &aObj)
{
    aFile >> aObj.longitude;
    aFile.ignore(256, ',');
    aFile >> aObj.altitude;
    aFile.ignore(256, ' ');
    return aFile;
}

void read_data()
{
    //ifstream file{"d:\\tmp\\tracks.tr"};
    // or
    ifstream file;
    file.open("d:\\tmp\\tracks.tr");

    if(!file)
        return;

    sPoint2DRead point;

    Navigation::TrackPoints2D track;

    while(!file.eof())
    {
        point = sPoint2DRead{0.,0.,""};
        file >> point;

        if(file.good())
            track.add(Navigation::Point2D{point.altitude, point.longitude});

        if(file.fail())
        {
            file.clear();
            break;
        }

        if(file.bad())
        {
            file.clear();
            break;
        }
    }

    file.close();
}
//------------------------------------------------------------------------------
double get_cin_double()
{
    double res = 0.0;

    cin >> res;
    if(cin.fail())
    {
        cin.clear();
        bool isSkip = true;
        char ch = '\0';
        for(;isSkip;)
        {
            cin >> ch;
            if(isdigit(ch))
            {
                cin.unget();
                isSkip = false;
                break;
            }
            switch (ch)
            {
            case '-':
            case '+':
            case '.':
                cin.unget();
                isSkip = false;
                break;
            }
        }
        cin >> res;
    }
    return res;
}

int main()
{
    //foo_a();
    //foo_b();

    //ofstream file;
    //file.open("d:\\tmp\\test.test",ios_base::binary);
    //file << 12;

    //int i = 12;
    //file.write((char*)&i, sizeof(int));
    //file.close();


    //read_data();

    cout << "result = " << get_cin_double() << endl;
    cout << "result = " << get_cin_double() << endl;
    cout << "result = " << get_cin_double() << endl;
    cout << "result = " << get_cin_double() << endl;
    cout << "result = " << get_cin_double() << endl;

    return 0;
}



















