#include "benderworldposition.h"

//------------------------------------------------------------------------------
benderWorldPosition::benderWorldPosition()
{
}
//------------------------------------------------------------------------------
benderWorldPosition::benderWorldPosition(int aLine, int aRow)
    :mLine(aLine)
    ,mRow(aRow)
{
}
//------------------------------------------------------------------------------
void benderWorldPosition::set(int aLine, int aRow)
{
    mLine = aLine;
    mRow = aRow;
}
//------------------------------------------------------------------------------
const int &benderWorldPosition::l()const
{
    return mLine;
}
//------------------------------------------------------------------------------
const int &benderWorldPosition::r()const
{
    return mRow;
}
//------------------------------------------------------------------------------
benderWorldPosition &benderWorldPosition::operator+=(eWorldDirection aDirection)
{
    switch(aDirection)
    {
        case eWorldDirection::SOUTH:
        {
            mLine += 1;
            break;
        }
        case eWorldDirection::EAST:
        {
            mRow += 1;
            break;
        }
        case eWorldDirection::NORTH:
        {
            mLine -= 1;
            break;
        }
        case eWorldDirection::WEST:
        {
            mRow -= 1;
            break;
        }
    }
    return *this;
}
//------------------------------------------------------------------------------
benderWorldPosition &benderWorldPosition::operator=(const benderWorldPosition &aRhs)
{
    mLine = aRhs.mLine;
    mRow  = aRhs.mRow;
    return *this;
}
//------------------------------------------------------------------------------
bool benderWorldPosition::operator==(const benderWorldPosition &aRhs)
{
    return (mLine == aRhs.mLine) && (mRow == aRhs.mRow);
}

// auxiliary functions
benderWorldPosition operator+(benderWorldPosition aPos, eWorldDirection aDirection)
{
    benderWorldPosition res = aPos;
    res += aDirection;
    return res;
}
