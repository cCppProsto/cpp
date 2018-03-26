#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void test();

private slots:

  void onResult(QNetworkReply*);


private:
  Ui::MainWindow *ui;

  QNetworkAccessManager networkManager;
};

#endif // MAINWINDOW_H
