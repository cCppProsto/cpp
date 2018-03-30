#include <QDebug>
#include "listviewitemdelegate.hpp"


listViewItemDelegate::listViewItemDelegate(QObject *aPobj)
  :QItemDelegate(aPobj)
{

}
void listViewItemDelegate::paint(QPainter* painter,
                                 const QStyleOptionViewItem& option,
                                 const QModelIndex& index) const
{
  QStyleOptionViewItem alignedOption(option);
  alignedOption.decorationAlignment = Qt::AlignCenter;
  alignedOption.decorationPosition = QStyleOptionViewItem::Top;

  QItemDelegate::paint(painter, alignedOption, index);
}

void listViewItemDelegate::drawFocus(QPainter *painter,
                                     const QStyleOptionViewItem &option,
                                     const QRect &rect) const
{

}
void listViewItemDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                         const QRect &rect, const QString &text) const
{

}

bool listViewItemDelegate::editorEvent(QEvent *event,
                                       QAbstractItemModel *model,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index)
{
  qWarning() << "Index = " << index.row();
  return QItemDelegate::editorEvent(event, model, option, index);
}









