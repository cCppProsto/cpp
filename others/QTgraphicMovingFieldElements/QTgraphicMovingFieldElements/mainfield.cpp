#include <QDebug>

#include "mainfield.hpp"

mainField::mainField()
  : field(10, 10, 70)
{
  init_cells();
}
//------------------------------------------------------------------------------
void mainField::init_cells()
{
  mvFields.resize(mLines*mColumns);

  for(int i = 0; i < mLines*mColumns; ++i)
    mvFields[i] = eCellType::EMPTY;

  mvFields[90] = eCellType::TYPE_2;
  mvFields[99] = eCellType::TYPE_1;

}

