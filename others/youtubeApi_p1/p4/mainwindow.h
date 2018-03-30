#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QNetworkAccessManager>
#include <QTimer>

#include "channel.hpp"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  void load_channels();

private slots:
  void imageUpdate();

private:
  std::vector<channel> mChannels;

  QStandardItemModel   mModel;
  QTimer               mTimer;
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
