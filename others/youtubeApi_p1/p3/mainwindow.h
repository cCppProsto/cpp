#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QNetworkAccessManager>
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
  channel *mpch;

  QStandardItemModel mModel;
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
