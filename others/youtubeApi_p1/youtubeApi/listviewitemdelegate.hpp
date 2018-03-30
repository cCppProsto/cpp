#ifndef LISTVIEWITEMDELEGATE_HPP
#define LISTVIEWITEMDELEGATE_HPP

#include <QItemDelegate>

class listViewItemDelegate : public QItemDelegate
{
public:
  listViewItemDelegate(QObject *);

  void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

  void drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
                         const QRect &rect) const;

  void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                           const QRect &rect, const QString &text) const;

  bool editorEvent(QEvent *event, QAbstractItemModel *model,
                   const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // LISTVIEWITEMDELEGATE_HPP
