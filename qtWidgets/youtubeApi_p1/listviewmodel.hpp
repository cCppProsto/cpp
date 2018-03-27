#ifndef LISTVIEWMODEL_HPP
#define LISTVIEWMODEL_HPP

#include <QAbstractItemModel>
#include <QFileIconProvider>
#include <QIcon>

class listViewModel : public QAbstractItemModel
{
public:
  listViewModel(QObject *parent = 0);

  QModelIndex index(int row, int column, const QModelIndex &parent) const override;
  QModelIndex parent(const QModelIndex &child) const override;

  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;

  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  bool hasChildren(const QModelIndex &parent) const override;


  QIcon services;
  QFileIconProvider iconProvider;
};

#endif // LISTVIEWMODEL_HPP
