#ifndef BENDER_H
#define BENDER_H

#include "common.h"
#include "bendermap.h"
#include "benderworldposition.h"
#include "gprimitive.hpp"

struct bender
{
    bender();
    ~bender();

    void attachMap(benderMap&);

    void move();
    void draw() const;
    const bool &isFinish() const;

private:
    bool _is_move(benderWorldPosition aPos)const;
    eWorldDirection _get_new_direction();

    void _screen_bender_move(eWorldDirection);
    void _screen_bender_create(benderWorldPosition aPos);
    void _screen_bender_teleport(benderWorldPosition aPos);

private:
    bool mIsFinish{false};
    bool mIsInvert{false};
    bool mIsBeer{false};
    int  mBenderSizeOnScreen{0};

    benderWorldPosition mPosition;
    eWorldDirection     meDirection = eWorldDirection::SOUTH;
    benderMap          *mpMap       = nullptr;
    gPrimitive         *mBenderObj  = nullptr;
};

#endif // BENDER_H
