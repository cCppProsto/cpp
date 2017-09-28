#ifndef VECTOR_H
#define VECTOR_H


namespace cpp_prosto
{
namespace math
{

struct vector
{
  /*
  vector();
  vector(const vector&);
  ~vector();
  double operator ! ();             //  Функция, вычисляющая длину вектора

  vector& operator ++ ();           //  Увеличение всех компонент вектора на единицу (префикс)
  vector operator ++ (int);         //  Увеличение всех компонент вектора
                                    //  на единицу (постфикс)
  vector& operator -- ();           //  Уменьшение всех компонент вектора
                                    //  на единицу (префикс)
  vector operator -- (int);         //  Уменьшение всех компонент вектора
                                    //  на единицу (постфикс)
  vector& operator = (const vector&); //  Перегруженный оператор присваивания

  vector& operator + ();              //  Перегруженный оператор + (унарный)

  vector operator - ();               //  Перегруженный оператор - (унарный)

  vector operator + (const vector&);  //  Сложение двух векторов

  vector operator + (double);         //  Сложение вектора с числом

  vector& operator += (const vector&);//  Перегруженный оператор += для сложения двух векторов

  vector& operator += (double);       //  Перегруженный оператор += для сложения вектора с числом

  vector operator - (const vector&);  //  Вычитание двух векторов

  vector operator - (double);         //  Вычитание числа из вектора

  vector& operator -= (const vector&);//  Перегруженный оператор -= для
                                      //  вычитания двух векторов
  vector& operator -= (double);       //  Перегруженный оператор -= для
                                      //  вычитания числа из вектора
  double operator * (const vector&);  //  Умножение векторов

  vector operator  *(double);         //  Умножение вектора на число

  vector& operator *= (double);       //  Перегруженный оператор *= для
                                      //  умножения вектора на число
*/
private:
  double x;
  double y;
};

}
}

#endif // VECTOR_H
