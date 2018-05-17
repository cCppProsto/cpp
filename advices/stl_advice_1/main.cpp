#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
  list<int> la{1,2,3,4,5,6,7,8,9};
  list<int> lb;

  // if( la.size() == 0) // not use
  // if( la.empty()) // use

  lb.splice(lb.begin(), la);

  return 0;
}
