#define template_max(name, type) int max##name(type a, type b) \
{\
return a > b ? a : b;\
}

template_max(Int, int);
template_max(Float, float);
template_max(UChar, unsigned char);


template<typename T>
T max(T a, T b)
{
  return a > b ? a : b;
}

//int max(int a, int b) {return a > b ? a : b;}
//int max(float a, float b) {return a > b ? a : b;}

int main()
{
  int ai = 0;
  int bi = 1;

  float af = 90;
  float bf = 1;

  max(ai, bi);          // жесткая типизация
  max(af, bf);          // жесткая типизация

  //max(ai, bf);        // Ошибка! в аргументах разные типы
                        // в шаблоне указан только один тип

  //max('0', 0);        // Ошибка! в аргументах разные типы
                        // в шаблоне указан только один тип

  max<int>('1', bf); // все аргументы будут приведены к типу int
  //max<double>(1, af);   // все аргументы будут приведены к типу double

  return 0;
}















