#include <QDebug>

#include "listviewdelegate.hpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"

//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->listView->setViewMode(QListView::ListMode);
  //ui->listView->setIconSize(QSize(240,240));
  //ui->listView->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
  //ui->listView->setResizeMode(QListView::Adjust);
  ui->listView->setResizeMode(QListView::Fixed);

  ui->listView->setItemDelegate(new listViewDelegate(ui->listView));

  mModel.setColumnCount(1);

  ui->listView->setModel(&mModel);
  load_stat();

  connect(&mTimer, SIGNAL(timeout()), SLOT(imageUpdate()));
  mTimer.setInterval(500);
  mTimer.start();
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
  delete ui;
}
//------------------------------------------------------------------------------
void MainWindow::imageUpdate()
{
  bool isStop = true;
  for(unsigned int i = 0; i < mCH.size(); ++i)
  {
    if(mCH[i].thumbIsLoaded())
    {
      if( !mModel.index(i,0).data(Qt::DecorationRole).isValid())
      {
        mModel.setData(mModel.index(i,0), mCH[i].pixmap(), Qt::DecorationRole);
        qWarning() << "loaded";
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
void MainWindow::load_stat()
{
  mCH.push_back(channel("UC_x5XG1OV2P6uZZ5FSM9Ttw", this));
  mCH.push_back(channel("UC_ehNByPcItZU3pXL-4skUA", this));
  mCH.push_back(channel("UCRijo3ddMTht_IHyNSNXpNQ", this));
  mCH.push_back(channel("UC5f5IV0Bf79YLp_p9nfInRA", this));
  mCH.push_back(channel("UCHJuQZuzapBh-CuhRYxIZrg", this));
  mCH.push_back(channel("UC5zBCJg6hYFwnBV2m4XG4kg", this));
  mCH.push_back(channel("UCgiO267R4Qo-SJF2UzH5ccQ", this));

  for(unsigned int i = 0; i < mCH.size(); ++i)
    mCH[i].fetchData();

  mModel.setRowCount(mCH.size());
}


/*
{
 "kind": "youtube#channelListResponse",
 "etag": "\"RmznBCICv9YtgWaaa_nWDIH1_GM/cZnF4vvOg72FSt8eEeDmBu9kZQI\"",
 "pageInfo": {
  "totalResults": 1,
  "resultsPerPage": 1
 },
  "items": [
  {
    "kind": "youtube#channel",
    "etag": "\"RmznBCICv9YtgWaaa_nWDIH1_GM/x6Vn-y_MrojfUvUS4XjSIu_PZRc\"",
    "id": "UC_x5XG1OV2P6uZZ5FSM9Ttw",
    "snippet":
    {
      "title": "Google Developers",
      "description": "The Google Developers ...",
      "customUrl": "googlecode",
      "publishedAt": "2007-08-23T00:34:43.000Z",

      "thumbnails":
      {
        "default":
        {
          "url": "https://yt3.ggpht.com/-Fgp8K ...",
          "width": 88,
          "height": 88
        },
        "medium":
        {
          "url": "https://yt3.ggpht.com/-Fgp8KF ...",
          "width": 240,
          "height": 240
        },
        "high":
        {
          "url": "https://yt3.ggpht.com/-Fgp8KFp ...",
          "width": 800,
          "height": 800
        }
      },
      "localized":
      {
        "title": "Google Developers",
        "description": "The Google Developers channel ..."
      }
    },
  "contentDetails":
  {
    "relatedPlaylists":
    {
      "uploads": "UU_x5XG1OV2P6uZZ5FSM9Ttw",
      "watchHistory": "HL",
      "watchLater": "WL"
    }
  },
  "statistics":
  {
    "viewCount": "130255233",
    "commentCount": "393",
    "subscriberCount": "1365920",
    "hiddenSubscriberCount": false,
    "videoCount": "4601"
  }
}
 ]
}
*/

















