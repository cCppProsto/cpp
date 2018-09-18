#include <iostream>

// Мейерс С. - Наиболее эффективное использование C++ - 2000 35 рекомендаций
// Правило 3 - Никогда не используйте полиморфизм в массивах

using namespace std;

struct BST
{
  BST(){}
  ~BST()
  {
    std::cout << "~BST()\n";
  }
  int m_i;
};

struct BalancedBST : public BST
{
  BalancedBST(){}
  ~BalancedBST()
  {
    std::cout << "~BalancedBST()\n";
  }

  int m_count;
};

void printBSTArray(const BST aArray[], int aLength)
{
  for(int i = 0; i < aLength; ++i)
    std::cout << aArray[i].m_i << ", ";

  std::cout << std::endl;
}

void deleteArray(BST aArray[])
{
  delete [] aArray;
}

int main()
{
  BST arr[10];
  arr[0].m_i = 0;
  arr[1].m_i = 1;
  arr[2].m_i = 2;
  arr[3].m_i = 3;
  arr[4].m_i = 4;
  arr[5].m_i = 5;
  arr[6].m_i = 6;
  arr[7].m_i = 7;
  arr[8].m_i = 8;
  arr[9].m_i = 9;

  BalancedBST bal_arr[10];
  bal_arr[0].m_i = 10;
  bal_arr[1].m_i = 9;
  bal_arr[2].m_i = 8;
  bal_arr[3].m_i = 7;
  bal_arr[4].m_i = 6;
  bal_arr[5].m_i = 5;
  bal_arr[6].m_i = 4;
  bal_arr[7].m_i = 3;
  bal_arr[8].m_i = 2;
  bal_arr[9].m_i = 1;

  printBSTArray(arr, 10);
  printBSTArray(bal_arr, 10);

  BST *b = new BalancedBST[10];
  deleteArray(b);

  cout << "Hello World!" << endl;
  return 0;
}
