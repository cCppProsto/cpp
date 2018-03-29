#include<QPainter>
#include<QDebug>

#include "listviewdelegate.hpp"

listViewDelegate::listViewDelegate(QObject *pobj)
  :QItemDelegate(pobj)
{
}
//------------------------------------------------------------------------------
void listViewDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  QStyleOptionViewItem alignedOption(option);
  alignedOption.decorationAlignment = Qt::AlignCenter;
  alignedOption.decorationPosition = QStyleOptionViewItem::Top;

  QItemDelegate::paint(painter, alignedOption, index);
}
//------------------------------------------------------------------------------
void listViewDelegate::drawFocus(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QRect &rect) const
{
}
/*
//------------------------------------------------------------------------------
QSize listViewDelegate::sizeHint(const QStyleOptionViewItem &option,
               const QModelIndex &index) const
{
  return QSize(100, 100);
}*/
//------------------------------------------------------------------------------
bool listViewDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                 const QStyleOptionViewItem &option, const QModelIndex &index)
{
  qWarning() << "Index = " << index.row();
  return QItemDelegate::editorEvent(event, model, option, index);
}

