#include <array>
#include <thread>
#include <chrono>

#include "gpnumber.hpp"
#include "gpplane.hpp"
#include "selectanimate.hpp"

using namespace cpp_prosto::graphical;

struct sortAnimateData
{
  enum class eAction
  {
    SWAP,
    COMPARE,
    SAVE
  };

  unsigned  mFirstIndex;
  unsigned  mSecondIndex;
  eAction   mAction;
  std::vector<unsigned> mArray;
};
//

struct selectAnim
{
  static constexpr unsigned sX{200};
  static constexpr unsigned sY{50};
  static constexpr unsigned width{50};
  static constexpr unsigned border{3};

  void init(std::vector<unsigned> &aVector)
  {
    mArray = aVector;
    mArrayDrawObj.resize(aVector.size());
    for(unsigned i = 0; i  < mArrayDrawObj.size(); ++i)
    {
      int x = sX + i*width + i*border;
      gpPlane tmp{{x, sY}, width, width};
      tmp.set_color(Color(eColorType::Red));
      mArrayDrawObj[i] = tmp;
    }

    mPlaneCompare.set_color(Color(eColorType::Green));
    mPlaneCompare.set_point_size(8);

    mPlaneSwap.set_color(Color(eColorType::Red));
    mPlaneSwap.set_fill_color(Color(eColorType::Blue));
    mPlaneSwap.set_point_size(4);

    mPlaneSave.set_color(Color(eColorType::Green));
    mPlaneSave.set_fill_color(Color(eColorType::Green));
    mPlaneSave.set_point_size(4);

    mNumber.set_color(Color(eColorType::White));
  }

  void sort()
  {
    unsigned end{(unsigned)mArray.size()};
    for(unsigned i = 0 ; i < end - 1; i++)
    {
      unsigned min_i = i;
      for(unsigned j = i + 1; j < end; ++j)
        if(less(j, min_i))
          min_i = savemin(j);

      if(min_i != i)
        swap(i, min_i);
    }
  }

  void frameReset()
  {
    mFameIndex = 0;
  }

  void draw()
  {
    mNumber.set_point({25, 25}, 0);
    mNumber.setValue(mFrames.size());
    mNumber.draw();

    draw_array();

    if(mFameIndex < mFrames.size())
    {
      draw_frame();
      if(mFameIndex < 20)
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      else
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      ++mFameIndex;
    }
    else
    {
      std::vector<unsigned> &arr = mArray;
      for(unsigned i = 0; i < arr.size(); ++i)
      {
        mNumber.set_point({(int)(sX + i*width + i*border + 25), (int)(sY + 25)}, 0);
        mNumber.setValue(arr[i]);
        mNumber.draw();
      }
    }
  }

private:
  void draw_array()
  {
    for(const auto &o : mArrayDrawObj)
      o.draw();
  }

  void draw_frame()
  {
    sortAnimateData &frame = mFrames[mFameIndex];

    switch(frame.mAction)
    {
      case sortAnimateData::eAction::SWAP:
      {
        unsigned x{sX + frame.mFirstIndex*width + frame.mFirstIndex*border};
        mPlaneSwap.set_point({(int)x,  sY},0);
        mPlaneSwap.draw();

        x = sX + frame.mSecondIndex*width + frame.mSecondIndex*border;
        mPlaneSwap.set_point({(int)x,  sY},0);
        mPlaneSwap.draw();
        break;
      }
      case sortAnimateData::eAction::COMPARE:
      {
        unsigned x{sX + frame.mFirstIndex*width + frame.mFirstIndex*border};
        mPlaneCompare.set_point({(int)x,  sY},0);
        mPlaneCompare.draw();

        x = sX + frame.mSecondIndex*width + frame.mSecondIndex*border;
        mPlaneCompare.set_point({(int)x,  sY},0);
        mPlaneCompare.draw();
        break;
      }
      case sortAnimateData::eAction::SAVE:
      {
        unsigned x{sX + frame.mFirstIndex*width + frame.mFirstIndex*border};
        mPlaneSave.set_point({(int)x,  sY},0);
        mPlaneSave.draw();
        break;
      }
    }

    std::vector<unsigned> &arr = mFrames[mFameIndex].mArray;
    for(unsigned i = 0; i < arr.size(); ++i)
    {
      mNumber.set_point({(int)(sX + i*width + i*border + 25), (int)(sY + 25)}, 0);
      mNumber.setValue(arr[i]);
      mNumber.draw();
    }
  }

  void swap(unsigned aFirst, unsigned aSecond)
  {
    sortAnimateData tmp;
    tmp.mArray      = mArray;
    tmp.mAction     = sortAnimateData::eAction::SWAP;
    tmp.mFirstIndex = aFirst;
    tmp.mSecondIndex= aSecond;
    mFrames.push_back(tmp);

    unsigned t{mArray[aFirst]};
    mArray[aFirst]  = mArray[aSecond];
    mArray[aSecond] = t;
  }

  bool less(unsigned aFirst, unsigned aSecond)
  {
    sortAnimateData tmp;
    tmp.mArray      = mArray;
    tmp.mAction     = sortAnimateData::eAction::COMPARE;
    tmp.mFirstIndex = aFirst;
    tmp.mSecondIndex= aSecond;
    mFrames.push_back(tmp);

    return mArray[aFirst] < mArray[aSecond];
  }

  unsigned savemin(unsigned aValue)
  {
    sortAnimateData tmp;
    tmp.mArray      = mArray;
    tmp.mAction     = sortAnimateData::eAction::SAVE;
    tmp.mFirstIndex = aValue;
    mFrames.push_back(tmp);

    return aValue;
  }

  std::vector<unsigned> mArray;
  std::vector<gpPlane>  mArrayDrawObj;
  gpPlane mPlane;

  unsigned mFameIndex{0};
  std::vector<sortAnimateData> mFrames;

  gpNumber  mNumber{{0,0}};
  gpPlane   mPlaneCompare{{0,0},50,50};
  gpPlane   mPlaneSwap{{0,0},50,50};
  gpPlane   mPlaneSave{{0,0},50,50};
};
static selectAnim gb;

//------------------------------------------------------------------------------
selectanimate::selectanimate()
{
}
void selectanimate::init(eType aType)
{
  switch(aType)
  {
    case eType::UNSORTED:
    {
      std::vector<unsigned> v = {10,9,8,7,6,5,4,3,2,1};
      gb.init(v);
      gb.sort();
      break;
    }
    case eType::SORTED:
    {
      std::vector<unsigned> v = {1,2,3,4,5,6,7,8,9,10};
      gb.init(v);
      gb.sort();
      break;
    }
    case eType::CUSTOM:
    {
    std::vector<unsigned> v = {1,2,3,4,5,10,6,7,8,9};
      gb.init(v);
      gb.sort();
      break;
    }
  }
}
//------------------------------------------------------------------------------
void selectanimate::draw()
{
  gb.draw();
}
