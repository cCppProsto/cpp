#include <QColor>
#include <QBrush>

#include "listviewmodel.hpp"

listViewModel::listViewModel(QObject *parent)
  :QAbstractItemModel(parent),
      services(QPixmap(":/pics/pics/folder.png"))
{
}

QModelIndex listViewModel::index(int row, int column, const QModelIndex &parent) const
{
//    if (row < rc && row >= 0 && column < cc && column >= 0) {
//        Node *parentNode = static_cast<Node*>(parent.internalPointer());
//        Node *childNode = node(row, parentNode);
//        if (childNode)
//            return createIndex(row, column, childNode);
//    }

  return createIndex(row, column);
  //return QModelIndex();
}

QModelIndex listViewModel::parent(const QModelIndex &child) const
{
//    if (child.isValid()) {
//        Node *childNode = static_cast<Node*>(child.internalPointer());
//        Node *parentNode = parent(childNode);
//        if (parentNode)
//            return createIndex(row(parentNode), 0, parentNode);
//    }
    return QModelIndex();
}

int listViewModel::rowCount(const QModelIndex &parent) const
{
    return 4;
}

int listViewModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant listViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return "";//QVariant("Item " + QString::number(index.row()) + ':' + QString::number(index.column()));

    if (role == Qt::DecorationRole)
    {
      return iconProvider.icon(QFileIconProvider::File);
    }
    return QVariant();
}

QVariant listViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        return QString::number(section);
    if (role == Qt::DecorationRole)
        return QVariant::fromValue(services);
    return QAbstractItemModel::headerData(section, orientation, role);
}

bool listViewModel::hasChildren(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return false;
    return true;
}
















