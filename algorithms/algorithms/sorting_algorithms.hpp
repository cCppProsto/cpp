#ifndef ALG_SORTS_HPP
#define ALG_SORTS_HPP

#include <vector>

template<typename T>
bool larger(T &aValue1, T &aValue2)
{
  return aValue1 > aValue2;
}

template<typename T>
bool less(T &aValue1, T &aValue2)
{
  return aValue1 < aValue2;
}

template<typename T>
void swap(T &aValue1, T &aValue2)
{
  T tmp;
  tmp = aValue1;
  aValue1 = aValue2;
  aValue2 = tmp;
}

template<typename Item>
void exch(Item &aA, Item &aB)
{
  Item t = aA;
  aA = aB;
  aB = t;
}

template<typename Item>
void compexch(Item &aA, Item &aB)
{
  if(aB < aA)
    exch(aA, aB);
}
//------------------------------------------------------------------------------

//-------------------- SELECT SORT ---------------------------------------------
template<typename T>
void select_sort(std::vector<T> &aVector)
{
  unsigned end = aVector.size();
  for(unsigned i = 0; i < end - 1; ++i)
  {
    unsigned min = i;
    for(unsigned j = i + 1; j < end; ++j)
      if(less(aVector[j], aVector[min]))
        min = j;
    swap(aVector[i], aVector[min]);
  }
}
//------------------------------------------------------------------------------

//-------------------- INSERT SORT ---------------------------------------------
template<typename T>
void insert_sort(std::vector<T> &aVector)
{
  unsigned end = aVector.size() - 1;
  for(unsigned i = end; i > 0; --i)
    if(larger(aVector[i-1], aVector[i]))
      swap(aVector[i-1], aVector[i]);

  for(unsigned i = 2; i <= end; ++i)
  {
    unsigned j = i;
    unsigned value = aVector[i];

    while(larger(aVector[j-1], value))
    {
      aVector[j] = aVector[j-1];
      --j;
    }
    aVector[j] = value;
  }
}
//------------------------------------------------------------------------------

//-------------------- BUBBLE SORT ---------------------------------------------
template<typename T>
void bubble_sort(std::vector<T> &aVector)
{
  unsigned end = aVector.size();
  for(unsigned i = 0 ; i < ( end - 1 ); i++)
    for (unsigned j = 0 ; j < end - i - 1; j++)
      if(larger(aVector[j], aVector[j+1]))
        swap(aVector[j], aVector[j+1]);
}
//------------------------------------------------------------------------------

//-------------------- SHELL SORT ----------------------------------------------
template <typename T>
void shell_sort(std::vector<T> &aVector)
{
  unsigned end = aVector.size() - 1;

  unsigned h;
  for(h = 1; h <= end/9; h = 3*h+1)
    ;

  for(; h > 0; h /= 3)
    for(auto i = h; i <= end; i++)
    {
      unsigned j = i;
      T v = aVector[i];
      while(j >= h && v < aVector[j - h])
      {
        aVector[j] = aVector[j - h];
        j -= h;
      }
      aVector[j] = v;
    }
}
//------------------------------------------------------------------------------

//-------------------- QUICK SORT ----------------------------------------------
template <class Item>
class STACK
{
private:
  Item *s{nullptr};
  int  N;

public:
  STACK(int maxN)
  {
    s = new Item[maxN];
    N = 0;
  }

  ~STACK()
  {
    if(s != nullptr)
      delete [] s;
  }
  bool empty() const
  {
    return N == 0;
  }
  void push(Item item)
  {
    s[N++] = item;
  }
  Item pop()
  {
    return s[--N];
  }
};


template<class Item>
int partition(Item aArray[], int aL, int aR)
{
  int i = aL - 1;
  int j = aR;
  Item v = aArray[aR];
  for(;;)
  {
    while(aArray[++i] < v)
      ;

    while(v < aArray[--j])
      if(j == aL)
        break;

    if( i >= j)
      break;

    exch(aArray[i], aArray[j]);
  }

  exch(aArray[i], aArray[aR]);
  return i;
}

inline void push2(STACK<int> &aS, int aA, int aB)
{
  aS.push(aB);
  aS.push(aA);
}

template<class Item>
void quicksort(Item aArray[], int aL, int aR)
{
  if(aR <= aL)
    return;

  int i = partition(aArray, aL, aR);
  quicksort(aArray, aL, i-1);
  quicksort(aArray, i+1, aR);
}

// N
template <class Item>
void quicksort_v2(Item aArray[], int aL, int aR)
{
  STACK<int> s(50);
  push2(s, aL, aR);
  while (!s.empty())
  {
    aL = s.pop();
    aR = s.pop();

    if (aR <= aL)
      continue;

    int i = partition(aArray, aL, aR);

    if (i-aL > aR-i)
    {
      push2(s, aL, i-1);
      push2(s, i+1, aR);
    }
    else
    {
      push2(s, i+1, aR);
      push2(s, aL, i-1);
    }
  }
}

static const int M = 10;
template <class Item>
void quicksort_v3(Item aArray[], int aL, int aR)
{
  if (aR-aL <= M)
    return;

  exch(aArray[(aL+aR)/2], aArray[aR-1]);

  compexch(aArray[aL], aArray[aR-1]);
  compexch(aArray[aL], aArray[aR]);
  compexch(aArray[aR-1], aArray[aR]);

  int i = partition(aArray, aL+1, aR-1);

  quicksort_v3(aArray, aL, i-1);
  quicksort_v3(aArray, i+1, aR);
}

template <class Item>
int operator==(const Item &A, const Item &B)
{
  return !less(A, B) && !less(B, A);
}

template <class Item>
void quicksort_v4(Item a[], int l, int r)
{
  int k;
  Item v = a[r];
  if (r <= l)
    return;

  int i = l-1, j = r, p = l-1, q = r;

  for (;;)
  {
    while (a[++i] < v)
      ;

    while (v < a[--j])
      if (j == l)
        break;

    if (i >= j)
      break;

    exch(a[i],a[j]);
    if (a[i] == v)
    {
      p++;
      exch(a[p],a[i]);
    }

    if (v == a[j])
    {
      q--;
      exch(a[q],a[j]);
    }
  }
  exch(a[i], a[r]); j = i-1; i = i+1;

  for (k = l  ; k <= p; k++, j--)
    exch(a[k],a[j]);

  for (k = r-1; k >= q; k--, i++)
    exch(a[k],a[i]);

  quicksort_v4(a, l, j);
  quicksort_v4(a, i, r);
}
//------------------------------------------------------------------------------


#endif // ALG_SORTS_HPP
