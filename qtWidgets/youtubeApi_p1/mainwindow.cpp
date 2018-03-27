// https://makina-corpus.com/blog/metier/archives/access-json-webservice-qt-c
// https://stackoverflow.com/questions/46851685/how-to-access-element-of-json-using-qt?rq=1
// https://developers.google.com/youtube/v3/code_samples/code_snippets
// https://developers.google.com/youtube/v3/docs/channels#statistics
// http://erickveil.github.io/2016/04/06/How-To-Manipulate-JSON-With-C++-and-Qt.html

#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <QDebug>
#include <QItemSelectionModel>

#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

#include "listviewdelegate.hpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"


//------------------------------------------------------------------------------
auto get_statistic_map(const QVariantMap &aMap)
{
  auto item = aMap["items"].toList().at(0);
  return item.toMap()["statistics"].toMap();
}
//------------------------------------------------------------------------------
auto get_thumbnails_map(const QVariantMap &aMap)
{
  auto item = aMap["items"].toList().at(0);
  auto snippet = item.toMap()["snippet"].toMap();

  return snippet["thumbnails"].toMap();
}
//------------------------------------------------------------------------------
void fill_ytStatistic(ytStatistic &aObj, const QVariantMap &aMap)
{
  aObj.commentCount           = aMap["commentCount"].toInt();
  aObj.subscriberCount        = aMap["subscriberCount"].toInt();
  aObj.viewCount              = aMap["viewCount"].toInt();
  aObj.videoCount             = aMap["videoCount"].toInt();
  aObj.hiddenSubscriberCount  = aMap["hiddenSubscriberCount"].toBool();
}
//------------------------------------------------------------------------------
void fill_ytThumbs(ytThumbnails &aObj, const QVariantMap &aMap)
{
  {
    auto r = aMap["default"].toMap();
    aObj.default_width  = r["width"].toInt();
    aObj.default_height = r["height"].toInt();;
    aObj.default_url    = r["url"].toString();
  }
  {
    auto r = aMap["medium"].toMap();
    aObj.medium_width  = r["width"].toInt();
    aObj.medium_height = r["height"].toInt();;
    aObj.medium_url    = r["url"].toString();
  }
  {
    auto r = aMap["high"].toMap();
    aObj.high_width  = r["width"].toInt();
    aObj.high_height = r["height"].toInt();;
    aObj.high_url    = r["url"].toString();
  }
}


//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->listView->setViewMode(QListView::ListMode);
  ui->listView->setIconSize(QSize(200,200));
  //ui->listView->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
  //ui->listView->setResizeMode(QListView::Adjust);
  //ui->listView->setResizeMode(QListView::Fixed);

  ui->listView->setItemDelegate(new listViewDelegate(ui->listView));

  stModel.setColumnCount(1);
  stModel.setRowCount(2);


  stModel.setData(stModel.index(0,0), QIcon(":/pics/pics/test.png"), Qt::DecorationRole);
  stModel.setData(stModel.index(1,0), QIcon(":/pics/pics/folder.png"), Qt::DecorationRole);

  ui->listView->setModel(&stModel);
  load_stat();
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
  delete ui;
}

// AIzaSyBQ1Azp81TRIgb68qR-Msc2S2ZrJzDvDUM

// https://www.googleapis.com/youtube/v3/videos?id=7lCDEYXw3mM&key=AIzaSyBQ1Azp81TRIgb68qR-Msc2S2ZrJzDvDUM
//     &part=snippet,contentDetails,statistics,status
//------------------------------------------------------------------------------
void MainWindow::load_stat()
{
  load_channel("UC_x5XG1OV2P6uZZ5FSM9Ttw");
  load_channel("UC_ehNByPcItZU3pXL-4skUA");
}
//------------------------------------------------------------------------------
void MainWindow::load_channel(QString aID)
{
  QUrl url("https://www.googleapis.com/youtube/v3/channels/");

  QUrlQuery query;
  query.addQueryItem("id",   aID);
  query.addQueryItem("part", "snippet,contentDetails,statistics");
  query.addQueryItem("key",  "AIzaSyBQ1Azp81TRIgb68qR-Msc2S2ZrJzDvDUM");
  url.setQuery(query);

  auto pnr = networkManager.get(QNetworkRequest(url));

  mChannels.push_back({false, pnr, aID,{},{}});

  connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
          this,            SLOT(onResult(QNetworkReply*)));

  // qWarning() << url.toString();
}
//------------------------------------------------------------------------------
void MainWindow::onResult(QNetworkReply *apReply)
{
  for(int i = 0; i < mChannels.size(); ++i)
  {
    if(mChannels[i].pNetworkReply == apReply)
    {
      QString data = (QString) apReply->readAll();

      QJsonDocument jsonDoc    = QJsonDocument::fromJson(data.toUtf8());
      QJsonObject   jsonObject = jsonDoc.object();
      QVariantMap   vmap       = jsonObject.toVariantMap();

      if(!vmap.empty())
      {
        fill_ytStatistic(mChannels[i].statistic, get_statistic_map(vmap));
        fill_ytThumbs(mChannels[i].thumbs, get_thumbnails_map(vmap));
        mChannels[i].isLoaded = true;
      }
    }
  }
  //auto keys     = vmap.keys();
  //auto kind     = vmap["kind"].toString();
  //auto etag     = vmap["etag"].toString();
  //auto pageInfo = vmap["pageInfo"].toMap();
  //QJsonArray jsonArray  = jsonObject["items"].toArray();
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

















