#include <iostream>
using namespace std;

enum eColor
{
    RED
   ,GREEN
   ,BLUE
   ,SOME
};

enum class eTankDirection
{
    UP
   ,RIGTH
   ,LEFT
   ,DOWN
};


enum class e1 : char
{
    yes
   ,no
   //, maybe = 200   // error - out of range -128...127
};

enum class e2 : unsigned char
{
    north
   ,east
   //, west = -1   // error - out of range 0...255
};

enum class e3 : short
{
    dec
   ,jan
};


eColor operator++(eColor &aObj)
{
    aObj = eColor(int(aObj)+1);

    if(aObj < RED )
    {
       aObj = SOME;
       return aObj;
    }

    if(aObj > SOME )
    {
        aObj = RED;
        return aObj;
    }

    return aObj;
}

eTankDirection operator++(eTankDirection &aObj)
{
    aObj = eTankDirection(int(aObj)+1);
    if(aObj < eTankDirection::UP )
    {
       aObj = eTankDirection::DOWN;
       return aObj;
    }

    if(aObj > eTankDirection::DOWN )
    {
        aObj = eTankDirection::UP;
        return aObj;
    }
    return aObj;
}

int main()
{
    int i = 0;

    {
        eColor color_a{RED};
        eColor color_b(RED);
        eColor color_c = RED;
        eColor color_d = eColor(RED);
        eColor color_e = eColor{RED};

        i = color_a;            // OK
        i = RED;                // OK

        //color_a = 0;          // error
        //color_a = 1;          // error

        color_a = (eColor)1;    // OK   - attention! range not checking
        color_a = eColor(10);   // OK   - attention! range not checking

        ++color_a;
        ++color_a;
    }

    {
        eTankDirection et_dir_a{eTankDirection::UP};
        eTankDirection et_dir_b(eTankDirection);
        eTankDirection et_dir_c = eTankDirection(eTankDirection::UP);
        eTankDirection et_dir_d = eTankDirection{eTankDirection::UP};

        //i = et_dir_a;                     // error
        //i = eTankDirection::UP;           // error

        i = int(eTankDirection::UP);        // - attention! range not checking
        i = (int)(eTankDirection::UP);      // - attention! range not checking

        //et_dir_a = 1;                     // error
        et_dir_a = eTankDirection(1);       // OK

        ++et_dir_a;
        ++et_dir_a;
    }


    return 0;
}
