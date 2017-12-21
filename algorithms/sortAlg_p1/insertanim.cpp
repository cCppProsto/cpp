#include <array>
#include <thread>
#include <chrono>

#include "insertanim.hpp"
#include "gpnumber.hpp"
#include "gpplane.hpp"

using namespace cpp_prosto::graphical;

struct sortAnimateData
{
  enum class eAction
  {
    SWAP,
    COMPARE,
    CHANGE_INDEX,
    CHANGE_VALUE
  };

  unsigned  mFirstIndex;
  unsigned  mSecondIndex;
  eAction   mAction;
  std::vector<unsigned> mArray;
};
//

struct insertAnim
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
    mPlaneSwap.set_fill_color(Color(eColorType::Red));
    mPlaneSwap.set_point_size(4);

    mPlaneChangeIndex.set_color(Color(eColorType::Red));
    mPlaneChangeIndex.set_fill_color(Color(eColorType::Red));
    mPlaneChangeIndex.set_point_size(4);

    mPlaneChangeValue.set_color(Color(eColorType::Purple));
    mPlaneChangeValue.set_fill_color(Color(eColorType::Purple));
    mPlaneChangeValue.set_point_size(4);

    mNumber.set_color(Color(eColorType::White));
  }

  void sort()
  {
    unsigned end = mArray.size() - 1;
    for(unsigned i = end; i > 0; --i)
      if(lager(i-1, i))
        swap(i-1, i);

    for(unsigned i = 2; i <= end; ++i)
    {
      unsigned j = i;
      unsigned value = mArray[i];

      while(value < mArray[j-1])
      {
        set_by_index(j, j-1);
        --j;
      }
      set_by_value(j, value);
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
      if(mFameIndex < 30)
        std::this_thread::sleep_for(std::chrono::milliseconds(1200));
      else
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
      case sortAnimateData::eAction::CHANGE_INDEX:
      {
        unsigned x{sX + frame.mFirstIndex*width + frame.mFirstIndex*border};
        mPlaneChangeIndex.set_point({(int)x,  sY},0);
        mPlaneChangeIndex.draw();

        x = sX + frame.mSecondIndex*width + frame.mSecondIndex*border;
        mPlaneChangeIndex.set_point({(int)x,  sY},0);
        mPlaneChangeIndex.draw();
        break;
      }
      case sortAnimateData::eAction::CHANGE_VALUE:
      {
        unsigned x{sX + frame.mFirstIndex*width + frame.mFirstIndex*border};
        mPlaneChangeValue.set_point({(int)x,  sY},0);
        mPlaneChangeValue.draw();
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

  bool lager(unsigned aFirst, unsigned aSecond)
  {
    sortAnimateData tmp;
    tmp.mArray      = mArray;
    tmp.mAction     = sortAnimateData::eAction::COMPARE;
    tmp.mFirstIndex = aFirst;
    tmp.mSecondIndex= aSecond;
    mFrames.push_back(tmp);

    return mArray[aFirst] > mArray[aSecond];
  }

  void set_by_index(unsigned aFirst, unsigned aSecond)
  {
    sortAnimateData tmp;
    tmp.mArray      = mArray;
    tmp.mAction     = sortAnimateData::eAction::CHANGE_INDEX;
    tmp.mFirstIndex = aFirst;
    tmp.mSecondIndex = aSecond;
    mFrames.push_back(tmp);
    mArray[aFirst] = mArray[aSecond];
  }

  void set_by_value(unsigned aFirst, unsigned aValue)
  {
    sortAnimateData tmp;
    tmp.mArray      = mArray;
    tmp.mAction     = sortAnimateData::eAction::CHANGE_VALUE;
    tmp.mFirstIndex = aFirst;
    mFrames.push_back(tmp);
    mArray[aFirst] = aValue;
  }

  std::vector<unsigned> mArray;
  std::vector<gpPlane>  mArrayDrawObj;
  gpPlane mPlane;

  unsigned mFameIndex{0};
  std::vector<sortAnimateData> mFrames;

  gpNumber  mNumber{{0,0}};
  gpPlane   mPlaneCompare{{0,0},50,50};
  gpPlane   mPlaneSwap{{0,0},50,50};
  gpPlane   mPlaneChangeIndex{{0,0},50,50};
  gpPlane   mPlaneChangeValue{{0,0},50,50};
};
static insertAnim gb;

//------------------------------------------------------------------------------
insertanimate::insertanimate()
{
}
void insertanimate::init(eType aType)
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
      std::vector<unsigned> v = {8,1,2,3,4,9,10,6,7};
      gb.init(v);
      gb.sort();
      break;
    }
  }
}
//------------------------------------------------------------------------------
void insertanimate::draw()
{
  gb.draw();
}
