#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QtNetwork/QNetworkAccessManager>
#include <QTimer>

#include <QStringList>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QAbstractItemView>

#include "channel.hpp"
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

private slots:
  void imageUpdate();

private:
  Ui::MainWindow *ui;

  QStandardItemModel    mModel;
  QNetworkAccessManager mNetworkManager;
  QVector<ytChannel>    mChannels;
  std::vector<channel>  mCH;
  QTimer                mTimer;
};

#endif // MAINWINDOW_H
