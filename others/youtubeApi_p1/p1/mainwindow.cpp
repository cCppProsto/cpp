#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listviewitemdelegate.hpp"

#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  //ui->listView->setViewMode(QListView::IconMode);

  ui->listView->setItemDelegate(new listViewItemDelegate(ui->listView));

  ui->listView->setModel(&mModel);
  mModel.setColumnCount(1);

  mModel.setRowCount(2);

  mModel.setData(mModel.index(0,0), QPixmap(":/pics/pics/test.png"), Qt::DecorationRole);
  mModel.setData(mModel.index(1,0), QPixmap(":/pics/pics/test.png"), Qt::DecorationRole);
}

MainWindow::~MainWindow()
{
  delete ui;
}
