#ifndef BENDERMAP_H
#define BENDERMAP_H

#include <string>
#include <vector>
#include <utility>

#include "common.h"
#include "benderworldposition.h"
#include "gprimitive.hpp"
#include "gpgrid.hpp"

using namespace cpp_prosto::graphical;

class benderMap
{
public:
    benderMap();
    ~benderMap();

    void load(std::string, int);

    const benderWorldPosition &getStartBenderPos()const;

    const eBenderMapObj &get(benderWorldPosition)const;

    const benderWorldPosition &teleport_1()const;
    const benderWorldPosition &teleport_2()const;

    const int &lines()const;
    const int &rows()const;
    const int &draw_object_height()const;

    void clear_field(benderWorldPosition);

    void draw() const;

private:
    void _create_wall(point2D, int);
    void _create_obtacle(point2D, int);
    void _create_finish(point2D, int);
    void _create_modifier_south(point2D, int);
    void _create_modifier_east(point2D, int);
    void _create_modifier_north(point2D, int);
    void _create_modifier_west(point2D, int);
    void _create_beer(point2D, int);
    void _create_invert(point2D, int);
    void _create_teleport(point2D, int);

private:
    using vectorObjects   = std::vector<std::pair<eBenderMapObj, gPrimitive*> >;
    using vectorTeleports = std::vector<benderWorldPosition>;

    int                 mRows{0};
    int                 mLines{0};
    int                 mDrawObjSize{0};
    benderWorldPosition mStartBenderPos;
    vectorObjects       mObjects;
    vectorTeleports     mTeleports;
    gpGrid              mGrid;
};

#endif // BENDERMAP_H
