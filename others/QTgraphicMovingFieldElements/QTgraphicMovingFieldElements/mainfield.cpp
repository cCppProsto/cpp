#include <QDebug>

#include "mainfield.hpp"

mainField::mainField()
  : field(10, 10, 70)
{
  init_vectors();
}
//------------------------------------------------------------------------------
void mainField::init_vectors()
{
  mvFields.resize(mLines*mColumns);

  for(int i = 0; i < mLines*mColumns; ++i)
    mvFields[i] = eFieldType::EMPTY;

  mvFields[90] = eFieldType::TYPE_2;
  mvFields[99] = eFieldType::TYPE_1;

}

