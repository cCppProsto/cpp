#include <iostream>

// Мейерс С. - Наиболее эффективное использование C++ - 2000 35 рекомендаций
// Правило 4 - Избегайте неоправданного использования констукторов по умолчанию

using namespace std;

struct sDouble
{
  sDouble()
    :v_1(0)
    ,v_2(0)
  {
  }
  int v_1;
  int v_2;
};

class EquipmentPiece
{
public:
  EquipmentPiece(int aIDNumber = UNSPECIFIED)
    :m_id(aIDNumber)
  {
  }

private:
  int m_id;
  static int UNSPECIFIED;
};

int EquipmentPiece::UNSPECIFIED = -1;

template<class T>
class Array
{
public:
  Array(int aSize)
  {
    data = new T[aSize];
  }
private:
  T *data;
};


int main()
{
  int id1, id2, id3;
  EquipmentPiece arr[] =
  {
    EquipmentPiece(id1)
   ,EquipmentPiece(id2)
   ,EquipmentPiece(id3)
  };

  EquipmentPiece **arr1 = new EquipmentPiece*[10];
  for(int i = 0; i < 10; ++i)
    arr1[i] = new EquipmentPiece(id1);

  void *rawMemory = operator new[](10*sizeof (EquipmentPiece));

  EquipmentPiece *arr2 = static_cast<EquipmentPiece*>(rawMemory);
  for(int i = 0; i < 10; ++i)
    new(&arr2[i])EquipmentPiece(i);

  operator delete[](rawMemory);
  delete [] arr2;

  EquipmentPiece obj;

  return 0;
}




















