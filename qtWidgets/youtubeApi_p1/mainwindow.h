#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QPair>
#include <QtNetwork/QNetworkAccessManager>

#include <QStringList>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QAbstractItemView>


#include "listviewmodel.hpp"

#include "common.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void load_stat();

private:
  void load_channel(QString);

private slots:

  void onResult(QNetworkReply*);

private:
  Ui::MainWindow *ui;

  listViewModel model;

  QStringListModel listModel;
  QStandardItemModel stModel;

  QNetworkAccessManager networkManager;
  QVector<ytChannel>    mChannels;
};

#endif // MAINWINDOW_H
