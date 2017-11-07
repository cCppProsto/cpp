#include <QKeyEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  qApp->installEventFilter(this);

  ui->label_2->setText("123esdfvasdfgv");


  ui->groupBoxAdmin->hide();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
  if(event->type() == QEvent::KeyPress)
  {
    if(watched == ui->btnSensor1)
    {
      QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
      if( keyEvent->key() == Qt::Key_Backspace)
      {
        ui->groupBoxMain->hide();
        ui->groupBoxAdmin->show();
      }
    }
  }

  if(event->type() == QEvent::Enter)
  {
    if(watched == ui->btnSensor1)
    {
      int f = 0;
    }

  }

  QObject::eventFilter(watched, event);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->groupBoxMain->show();
    ui->groupBoxAdmin->hide();
}
