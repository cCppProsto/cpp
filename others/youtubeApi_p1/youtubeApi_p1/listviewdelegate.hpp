#ifndef LISTVIEWDELEGATE_HPP
#define LISTVIEWDELEGATE_HPP

#include <QItemDelegate>

class listViewDelegate : public QItemDelegate
{
public:
  listViewDelegate(QObject *);

  void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;


  void drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
                         const QRect &rect) const;
  bool editorEvent(QEvent *event, QAbstractItemModel *model,
                   const QStyleOptionViewItem &option, const QModelIndex &index);

//  QSize sizeHint(const QStyleOptionViewItem &option,
//                 const QModelIndex &index) const;

};

#endif // LISTVIEWDELEGATE_HPP
