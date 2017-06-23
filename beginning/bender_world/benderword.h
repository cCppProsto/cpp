#ifndef BENDERWORD_H
#define BENDERWORD_H

#include <string>

#include "bendermap.h"
#include "bender.h"
#include "common.h"

using namespace cpp_prosto::graphical;

struct benderWord
{
    benderWord();

    void loadMap(std::string);

    void setScreenHeight(int);

    void step();
    void draw() const;

private:
    int mScreenHeight{0};
    int mFieldWidth{0};
    int mFieldHeight{0};

    benderMap mMap;
    bender    mBender;
};

#endif // BENDERWORD_H
