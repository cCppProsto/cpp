#include "benderword.h"
#include "gpplane.hpp"


//------------------------------------------------------------------------------
benderWord::benderWord()
{
}
//------------------------------------------------------------------------------
void benderWord::loadMap(std::string aPath)
{
    mMap.load(aPath, mScreenHeight);

    mFieldHeight = mScreenHeight / mMap.lines();

    mBender.attachMap(mMap);
}
//------------------------------------------------------------------------------
void benderWord::setScreenHeight(int aHeight)
{
    mScreenHeight = aHeight;
}
//------------------------------------------------------------------------------
void benderWord::step()
{
    mBender.move();
}
//------------------------------------------------------------------------------
void benderWord::draw() const
{
    mMap.draw();
    mBender.draw();
}
