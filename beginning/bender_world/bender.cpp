#include "bender.h"
#include "gpplane.hpp"

eWorldDirection operator++(eWorldDirection &aDir)
{
    using wd = eWorldDirection;
    aDir = (aDir == wd::WEST) ? wd::SOUTH : wd(int(aDir) + 1);
    return aDir;
}

eWorldDirection operator--(eWorldDirection &aDir)
{
    using wd = eWorldDirection;
    aDir = (aDir == wd::SOUTH) ? wd::WEST : wd(int(aDir) - 1);
    return aDir;
}

//------------------------------------------------------------------------------
bender::bender()
{
}
//------------------------------------------------------------------------------
bender::~bender()
{
    if(mBenderObj != nullptr)
        delete mBenderObj;
}
//------------------------------------------------------------------------------
void bender::attachMap(benderMap &arMap)
{
    mpMap = &arMap;

    mBenderSizeOnScreen = mpMap->draw_object_height();
    mPosition = mpMap->getStartBenderPos();

    _screen_bender_create(mPosition);
}
//------------------------------------------------------------------------------
void bender::move()
{
    if(mIsFinish)
        return;

    auto np   = mPosition + meDirection;
    auto &obj = mpMap->get(np);

    switch (obj)
    {
        using mo = eBenderMapObj;

        case mo::UNKNOWN:
        case mo::BENDER:
            break;
        case mo::WALL:
        {
            meDirection = _get_new_direction();
            break;
        }
        case mo::EMPTY:
        {
            mPosition += meDirection;
            _screen_bender_move(meDirection);
            break;
        }
        case mo::OBSTACLE:
        {
            if(mIsBeer)
            {
                mpMap->clear_field(mPosition + meDirection);
                mPosition += meDirection;
                _screen_bender_move(meDirection);
            }
            else
                meDirection = _get_new_direction();

            break;
        }
        case mo::FINISH:
        {
            mPosition += meDirection;
            _screen_bender_move(meDirection);
            mIsFinish = true;
            break;
        }
        case mo::SOUTH:
        {
            mPosition += meDirection;
            _screen_bender_move(meDirection);
            meDirection = eWorldDirection::SOUTH;
            break;
        }
        case mo::EAST:
        {
            mPosition += meDirection;
            _screen_bender_move(meDirection);
            meDirection = eWorldDirection::EAST;
            break;
        }
        case mo::NORTH:
        {
            mPosition += meDirection;
            _screen_bender_move(meDirection);
            meDirection = eWorldDirection::NORTH;
            break;
        }
        case mo::WEST:
        {
            mPosition += meDirection;
            _screen_bender_move(meDirection);
            meDirection = eWorldDirection::WEST;
            break;
        }
        case mo::BEER:
        {
            mPosition += meDirection;
            _screen_bender_move(meDirection);
            mIsBeer = mIsBeer ? false : true;
            break;
        }
        case mo::INVERT:
        {
            mPosition += meDirection;
            _screen_bender_move(meDirection);
            mIsInvert = mIsInvert ? false : true;
            break;
        }
        case mo::TELEPORT:
        {
            auto &t1 = mpMap->teleport_1();
            auto &t2 = mpMap->teleport_2();

            mPosition = (np == t1) ? t2 : t1;

            _screen_bender_teleport(mPosition);
            break;
        }
    }
}
//------------------------------------------------------------------------------
void bender::draw() const
{
    if(mBenderObj != nullptr)
        mBenderObj->draw();
}
//------------------------------------------------------------------------------
const bool &bender::isFinish() const
{
    return mIsFinish;
}
//------------------------------------------------------------------------------
bool bender::_is_move(benderWorldPosition aPos)const
{
    using mo = eBenderMapObj;
    auto &obj = mpMap->get(aPos);
    switch(obj)
    {
        case mo::UNKNOWN:
        case mo::WALL:
        {
            return false;
        }
        case mo::OBSTACLE:
        {
            if(mIsBeer)
                return true;
            return false;
        }
        case mo::BENDER:
        case mo::EMPTY:
        case mo::FINISH:
        case mo::SOUTH:
        case mo::EAST:
        case mo::NORTH:
        case mo::WEST:
        case mo::BEER:
        case mo::INVERT:
        case mo::TELEPORT:
        {
            return true;
        }
    }
    return false;
}
//------------------------------------------------------------------------------
eWorldDirection bender::_get_new_direction()
{
    eWorldDirection res = eWorldDirection::SOUTH;
    if(mIsInvert)
    {
        res = eWorldDirection::WEST;
        while (!_is_move(mPosition + res))
            --res;
        return res;
    }
    else
    {
        res = eWorldDirection::SOUTH;
        while (!_is_move(mPosition + res))
            ++res;
        return res;
    }
    return res;
}
//------------------------------------------------------------------------------
void bender::_screen_bender_move(eWorldDirection aDir)
{
    switch(aDir)
    {
        case eWorldDirection::SOUTH:
        {
            mBenderObj->move(0, mBenderSizeOnScreen);
            break;
        }
        case eWorldDirection::EAST:
        {
            mBenderObj->move(mBenderSizeOnScreen, 0);
            break;
        }
        case eWorldDirection::NORTH:
        {
            mBenderObj->move(0, -mBenderSizeOnScreen);
            break;
        }
        case eWorldDirection::WEST:
        {
            mBenderObj->move(-mBenderSizeOnScreen, 0);
            break;
        }
    }
}
//------------------------------------------------------------------------------
void bender::_screen_bender_create(benderWorldPosition aPos)
{
    if(mBenderObj != nullptr)
        delete mBenderObj;

    mBenderObj = new gpPlane({aPos.r()*mBenderSizeOnScreen, aPos.l()*mBenderSizeOnScreen},
                             mBenderSizeOnScreen,
                             mBenderSizeOnScreen);
    mBenderObj->set_color(Color(eColorType::Blue));
    mBenderObj->set_fill_color(Color(eColorType::Blue));
}
//------------------------------------------------------------------------------
void bender::_screen_bender_teleport(benderWorldPosition aPos)
{
    point2D cur_pos = mBenderObj->point(0);
    point2D new_pos{aPos.r()*mBenderSizeOnScreen, aPos.l()*mBenderSizeOnScreen};

    mBenderObj->move(new_pos.x - cur_pos.x, new_pos.y - cur_pos.y);
}
