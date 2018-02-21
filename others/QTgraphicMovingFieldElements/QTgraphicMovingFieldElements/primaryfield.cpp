#include <QDebug>

#include "primaryfield.hpp"

primaryField::primaryField()
  : field(3, 4, 70)
{
  init_vectors();
}
//------------------------------------------------------------------------------
void primaryField::init_vectors()
{
  mvFields.resize(mLines*mColumns);
  for(int i = 0; i < mLines*mColumns; ++i)
    mvFields[i] = eFieldType::EMPTY;
}
