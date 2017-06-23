#include "bendermap.h"

#include <fstream>
#include <limits>

#include "gpplane.hpp"
#include "gptriangle.hpp"
#include "gpcircle.hpp"
using namespace cpp_prosto::graphical;

//------------------------------------------------------------------------------
benderMap::benderMap()
{
}
//------------------------------------------------------------------------------
benderMap::~benderMap()
{
    auto i   = mObjects.begin();
    auto end = mObjects.end();
    while (i != end)
    {
        if((*i).second != nullptr)
        {
            delete (*i).second;
            (*i).second = nullptr;
        }
        ++i;
    }
}
//------------------------------------------------------------------------------
void benderMap::load(std::string aPath, int aScreenHeight)
{
    std::ifstream file{aPath};

    file >> mLines;
    file >> mRows;

    mDrawObjSize = aScreenHeight / mLines;

    mObjects.resize(mLines * mRows, {eBenderMapObj::UNKNOWN, nullptr});

    for(int l = 0; l < mLines; ++l)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for(int r = 0; r < mRows; ++r)
        {
            int x = r * mDrawObjSize;
            int y = l * mDrawObjSize;
            switch (file.get())
            {
                case ' ':
                {
                    mObjects[mRows*l + r].first = eBenderMapObj::EMPTY;
                    break;
                }
                case '@':
                {
                    mStartBenderPos.set(l, r);
                    mObjects[mRows*l + r].first = eBenderMapObj::EMPTY;
                    break;
                }
                case '#':
                {
                    _create_wall({x, y}, mRows*l + r);
                    break;
                }
                case 'X':
                {
                    _create_obtacle({x, y}, mRows*l + r);
                    break;
                }
                case '$':
                {
                    _create_finish({x, y}, mRows*l + r);
                    break;
                }
                case 'S':
                {
                    _create_modifier_south({x, y}, mRows*l + r);
                    break;
                }
                case 'E':
                {
                    _create_modifier_east({x, y}, mRows*l + r);
                    break;
                }
                case 'N':
                {
                    _create_modifier_north({x, y}, mRows*l + r);
                    break;
                }
                case 'W':
                {
                    _create_modifier_west({x, y}, mRows*l + r);
                    break;
                }
                case 'B':
                {
                    _create_beer({x, y}, mRows*l + r);
                    break;
                }
                case 'I':
                {
                    _create_invert({x, y}, mRows*l + r);
                    break;
                }
                case 'T':
                {
                    mTeleports.push_back(benderWorldPosition(l, r));
                    _create_teleport({x, y}, mRows*l + r);
                  break;
                }
            }
        }
    }
    file.close();

    mGrid.set(point2D{0, 0}, mDrawObjSize, mDrawObjSize, mLines, mRows);
    mGrid.set_color(Color(eColorType::Green));
}
//------------------------------------------------------------------------------
const int &benderMap::lines()const
{
    return mLines;
}
//------------------------------------------------------------------------------
const int &benderMap::rows()const
{
    return mRows;
}
//------------------------------------------------------------------------------
const int &benderMap::draw_object_height()const
{
    return mDrawObjSize;
}
//------------------------------------------------------------------------------
const eBenderMapObj &benderMap::get(benderWorldPosition aPos)const
{
    return mObjects[mRows*aPos.l() + aPos.r()].first;
}
//------------------------------------------------------------------------------
const benderWorldPosition &benderMap::getStartBenderPos()const
{
    return mStartBenderPos;
}
//------------------------------------------------------------------------------
void benderMap::clear_field(benderWorldPosition aPos)
{
    mObjects[mRows*aPos.l() + aPos.r()].first = eBenderMapObj::EMPTY;
}
//------------------------------------------------------------------------------
const benderWorldPosition &benderMap::teleport_1()const
{
    return mTeleports[0];
}
//------------------------------------------------------------------------------
const benderWorldPosition &benderMap::teleport_2()const
{
    return mTeleports[1];
}
//------------------------------------------------------------------------------
void benderMap::draw() const
{
    mGrid.draw();

    auto i = mObjects.begin();
    auto end = mObjects.end();
    while (i != end)
    {
        if((*i).second != nullptr)
            if((*i).first != eBenderMapObj::EMPTY)
                (*i).second->draw();
        ++i;
    }
}
//------------------------------------------------------------------------------
void benderMap::_create_wall(point2D aPos, int aIndex)
{
    mObjects[aIndex].first = eBenderMapObj::WALL;

    gPrimitive *plane = new gpPlane(aPos, mDrawObjSize, mDrawObjSize);
    plane->set_color(Color(eColorType::Green));
    plane->set_fill_color(Color(eColorType::Red));
    mObjects[aIndex].second = plane;
}
//------------------------------------------------------------------------------
void benderMap::_create_obtacle(point2D aPos, int aIndex)
{
    mObjects[aIndex].first = eBenderMapObj::OBSTACLE;

    gpCircle   *circle = new gpCircle(mDrawObjSize/2,
                                      11,
                                      {aPos.x + mDrawObjSize/2, aPos.y + mDrawObjSize/2});
    circle->set_color(Color(eColorType::Purple));
    mObjects[aIndex].second = circle;
}
//------------------------------------------------------------------------------
void benderMap::_create_finish(point2D aPos, int aIndex)
{
    mObjects[aIndex].first = eBenderMapObj::FINISH;

    gPrimitive *plane = new gpPlane(aPos, mDrawObjSize, mDrawObjSize);
    plane->set_color(Color(eColorType::Fuchsia));
    plane->set_fill_color(Color(eColorType::Fuchsia));
    mObjects[aIndex].second = plane;
}
//------------------------------------------------------------------------------
void benderMap::_create_modifier_south(point2D aPos, int aIndex)
{
    mObjects[aIndex].first = eBenderMapObj::SOUTH;

    point2D p1{aPos};
    point2D p2{aPos.x + mDrawObjSize,   aPos.y };
    point2D p3{aPos.x + mDrawObjSize/2, aPos.y + mDrawObjSize};

    gpTriangle *triangle = new gpTriangle(p1, p2, p3);
    triangle->set_color(Color(eColorType::Teal));
    triangle->set_fill_color(Color(eColorType::Teal));
    mObjects[aIndex].second = triangle;
}
//------------------------------------------------------------------------------
void benderMap::_create_modifier_east(point2D aPos, int aIndex)
{
    mObjects[aIndex].first = eBenderMapObj::EAST;

    point2D p1{aPos};
    point2D p2{aPos.x + mDrawObjSize, aPos.y + mDrawObjSize/2};
    point2D p3{aPos.x, aPos.y + mDrawObjSize};

    gpTriangle *triangle = new gpTriangle(p1, p2, p3);
    triangle->set_color(Color(eColorType::Teal));
    triangle->set_fill_color(Color(eColorType::Teal));
    mObjects[aIndex].second = triangle;

}
//------------------------------------------------------------------------------
void benderMap::_create_modifier_north(point2D aPos, int aIndex)
{
    mObjects[aIndex].first = eBenderMapObj::NORTH;

    point2D p1{aPos.x, aPos.y + mDrawObjSize};
    point2D p2{aPos.x + mDrawObjSize,   aPos.y + mDrawObjSize};
    point2D p3{aPos.x + mDrawObjSize/2, aPos.y};

    gpTriangle *triangle = new gpTriangle(p1, p2, p3);
    triangle->set_color(Color(eColorType::Teal));
    triangle->set_fill_color(Color(eColorType::Teal));
    mObjects[aIndex].second = triangle;
}
//------------------------------------------------------------------------------
void benderMap::_create_modifier_west(point2D aPos, int aIndex)
{
    mObjects[aIndex].first = eBenderMapObj::WEST;

    point2D p1{aPos.x + mDrawObjSize, aPos.y};
    point2D p2{aPos.x, aPos.y + mDrawObjSize/2};
    point2D p3{aPos.x + mDrawObjSize, aPos.y + mDrawObjSize};

    gpTriangle *triangle = new gpTriangle(p1, p2, p3);
    triangle->set_color(Color(eColorType::Teal));
    triangle->set_fill_color(Color(eColorType::Teal));
    mObjects[aIndex].second = triangle;
}
//------------------------------------------------------------------------------
void benderMap::_create_beer(point2D aPos, int aIndex)
{
    mObjects[aIndex].first = eBenderMapObj::BEER;

    gpCircle   *circle = new gpCircle(mDrawObjSize/2,
                                      11,
                                      {aPos.x + mDrawObjSize/2, aPos.y + mDrawObjSize/2});
    circle->set_color(Color(eColorType::Yellow));
    circle->set_fill_color(Color(eColorType::Yellow));
    mObjects[aIndex].second = circle;
}
//------------------------------------------------------------------------------
void benderMap::_create_invert(point2D aPos, int aIndex)
{
    mObjects[aIndex].first = eBenderMapObj::INVERT;

    gpCircle   *circle = new gpCircle(mDrawObjSize/2,
                                      7,
                                      {aPos.x + mDrawObjSize/2, aPos.y + mDrawObjSize/2});
    circle->set_color(Color(eColorType::Gray));
    mObjects[aIndex].second = circle;
}
//------------------------------------------------------------------------------
void benderMap::_create_teleport(point2D aPos, int aIndex)
{
    mObjects[aIndex].first = eBenderMapObj::TELEPORT;

    gpCircle   *circle = new gpCircle(mDrawObjSize/4,
                                      11,
                                      {aPos.x + mDrawObjSize/2, aPos.y + mDrawObjSize/2});
    circle->set_color(Color(eColorType::Green));
    circle->set_fill_color(Color(eColorType::Green));
    mObjects[aIndex].second = circle;

}

