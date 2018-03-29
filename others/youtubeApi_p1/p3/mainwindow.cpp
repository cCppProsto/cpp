// https://developers.google.com/youtube/v3/
// https://developers.google.com/youtube/v3/docs/
// https://developers.google.com/youtube/v3/getting-started
// https://developers.google.com/apis-explorer/?hl=ru#p/youtube/v3/
// https://developers.google.com/youtube/v3/docs/videos/list
// https://developers.google.com/youtube/v3/code_samples/code_snippets
// https://developers.google.com/youtube/v3/docs/channels#statistics

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

  mpch = new channel("UC_x5XG1OV2P6uZZ5FSM9Ttw",this);
  mpch->fetchData();
}

MainWindow::~MainWindow()
{
  delete ui;
}
