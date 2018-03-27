// https://github.com/radekp/qt/blob/master/src/gui/itemviews/qitemdelegate.cpp

#include<QPainter>

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
  return QItemDelegate::editorEvent(event, model, option, index);
}


/*
QStyleOptionViewItemV4 opt = setOptions(index, option);

const QStyleOptionViewItemV2 *v2 = qstyleoption_cast<const QStyleOptionViewItemV2 *>(&option);
opt.features = v2 ? v2->features
                : QStyleOptionViewItemV2::ViewItemFeatures(QStyleOptionViewItemV2::None);
const QStyleOptionViewItemV3 *v3 = qstyleoption_cast<const QStyleOptionViewItemV3 *>(&option);
opt.locale = v3 ? v3->locale : QLocale();
opt.widget = v3 ? v3->widget : 0;

// prepare
painter->save();

// get the data and the rectangles

QVariant value;

QPixmap pixmap;
QRect decorationRect;
value = index.data(Qt::DecorationRole);
if (value.isValid())
{
    // ### we need the pixmap to call the virtual function
    pixmap = decoration(opt, value);
    if (value.type() == QVariant::Icon)
    {
//          d->tmp.icon = qvariant_cast<QIcon>(value);
//          d->tmp.mode = d->iconMode(option.state);
//          d->tmp.state = d->iconState(option.state);
//          const QSize size = d->tmp.icon.actualSize(option.decorationSize,
//                                                    d->tmp.mode, d->tmp.state);
        decorationRect = QRect(QPoint(0, 0), QSize(60,60));
    }
    else
    {
        //d->tmp.icon = QIcon();
        decorationRect = QRect(QPoint(0, 0), pixmap.size());
    }
} else {
    //d->tmp.icon = QIcon();
    decorationRect = QRect();
}

QString text;
QRect displayRect;
value = index.data(Qt::DisplayRole);
if (value.isValid() && !value.isNull())
{
//      text = QItemDelegatePrivate::valueToText(value, opt);
//      displayRect = textRectangle(painter, d->textLayoutBounds(opt), opt.font, text);
}

QRect checkRect;
Qt::CheckState checkState = Qt::Unchecked;
value = index.data(Qt::CheckStateRole);
if (value.isValid())
{
//      checkState = static_cast<Qt::CheckState>(value.toInt());
//      checkRect = check(opt, opt.rect, value);
}

// do the layout

doLayout(opt, &checkRect, &decorationRect, &displayRect, false);

// draw the item

drawBackground(painter, opt, index);
drawCheck(painter, opt, checkRect, checkState);
drawDecoration(painter, opt, decorationRect, pixmap);
drawDisplay(painter, opt, displayRect, text);
//drawFocus(painter, opt, displayRect);

// done
painter->restore();
*/

