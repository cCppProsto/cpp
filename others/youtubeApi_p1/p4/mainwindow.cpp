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

//------------------------------------------------------------------------------
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

  load_channels();

  connect(&mTimer, SIGNAL(timeout()), SLOT(imageUpdate()));
  mTimer.setInterval(500);
  mTimer.start();

  //mModel.setData(mModel.index(0,0), QPixmap(":/pics/pics/test.png"), Qt::DecorationRole);
  //mModel.setData(mModel.index(1,0), QPixmap(":/pics/pics/test.png"), Qt::DecorationRole);
}
//------------------------------------------------------------------------------
void MainWindow::load_channels()
{
  mChannels.push_back(channel("UC_x5XG1OV2P6uZZ5FSM9Ttw", this));
  mChannels.push_back(channel("UC_ehNByPcItZU3pXL-4skUA", this));
  mChannels.push_back(channel("UCRijo3ddMTht_IHyNSNXpNQ", this));
  mChannels.push_back(channel("UC5f5IV0Bf79YLp_p9nfInRA", this));
  mChannels.push_back(channel("UCHJuQZuzapBh-CuhRYxIZrg", this));
  mChannels.push_back(channel("UC5zBCJg6hYFwnBV2m4XG4kg", this));
  mChannels.push_back(channel("UCgiO267R4Qo-SJF2UzH5ccQ", this));

  for(unsigned int i = 0; i < mChannels.size(); ++i)
    mChannels[i].fetchData();

  mModel.setRowCount(mChannels.size());
}
//------------------------------------------------------------------------------
void MainWindow::imageUpdate()
{
  bool isStop = true;
  for(unsigned int i = 0; i < mChannels.size(); ++i)
  {
    if(mChannels[i].thumbIsLoaded())
    {
      if( !mModel.index(i,0).data(Qt::DecorationRole).isValid())
      {
        mModel.setData(mModel.index(i,0), mChannels[i].pixmap(), Qt::DecorationRole);
      }
    }
    else
    {
      isStop = false;
    }
  }
  if(isStop)
    mTimer.stop();
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
  delete ui;
}
