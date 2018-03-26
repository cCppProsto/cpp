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


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  test();
}

MainWindow::~MainWindow()
{
  delete ui;
}

// AIzaSyBQ1Azp81TRIgb68qR-Msc2S2ZrJzDvDUM

// https://www.googleapis.com/youtube/v3/videos?id=7lCDEYXw3mM&key=AIzaSyBQ1Azp81TRIgb68qR-Msc2S2ZrJzDvDUM
//     &part=snippet,contentDetails,statistics,status

void MainWindow::test()
{
  QUrl url("https://www.googleapis.com/youtube/v3/channels/");

  QUrlQuery query;
  query.addQueryItem("id","UC_x5XG1OV2P6uZZ5FSM9Ttw");
  query.addQueryItem("part","snippet,contentDetails,statistics");
  query.addQueryItem("key","AIzaSyBQ1Azp81TRIgb68qR-Msc2S2ZrJzDvDUM");
  url.setQuery(query);

  connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
          this,            SLOT(onResult(QNetworkReply*)));

  qWarning() << url.toString();

  networkManager.get(QNetworkRequest(url));
}


void MainWindow::onResult(QNetworkReply *apReply)
{
  QString data = (QString) apReply->readAll();

  QJsonDocument jsonDoc    = QJsonDocument::fromJson(data.toUtf8());
  QJsonObject   jsonObject = jsonDoc.object();

  QVariantMap vmap = jsonObject.toVariantMap();

  auto keys     = vmap.keys();
  auto kind     = vmap["kind"].toString();
  auto etag     = vmap["etag"].toString();
  auto pageInfo = vmap["pageInfo"].toMap();

  auto item_0    = vmap["items"].toList().at(0);
  auto statistic = item_0.toMap()["statistics"];

  QJsonArray jsonArray  = jsonObject["items"].toArray();
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
   "snippet": {
    "title": "Google Developers",
    "description": "The Google Developers channel features talks from events, educational series, best practices, tips, and the latest updates across our products and platforms.",
    "customUrl": "googlecode",
    "publishedAt": "2007-08-23T00:34:43.000Z",
    "thumbnails": {
     "default": {
      "url": "https://yt3.ggpht.com/-Fgp8KFpgQqE/AAAAAAAAAAI/AAAAAAAAAAA/Wyh1vV5Up0I/s88-c-k-no-mo-rj-c0xffffff/photo.jpg",
      "width": 88,
      "height": 88
     },
     "medium": {
      "url": "https://yt3.ggpht.com/-Fgp8KFpgQqE/AAAAAAAAAAI/AAAAAAAAAAA/Wyh1vV5Up0I/s240-c-k-no-mo-rj-c0xffffff/photo.jpg",
      "width": 240,
      "height": 240
     },
     "high": {
      "url": "https://yt3.ggpht.com/-Fgp8KFpgQqE/AAAAAAAAAAI/AAAAAAAAAAA/Wyh1vV5Up0I/s800-c-k-no-mo-rj-c0xffffff/photo.jpg",
      "width": 800,
      "height": 800
     }
    },
    "localized": {
     "title": "Google Developers",
     "description": "The Google Developers channel features talks from events, educational series, best practices, tips, and the latest updates across our products and platforms."
    }
   },
   "contentDetails": {
    "relatedPlaylists": {
     "uploads": "UU_x5XG1OV2P6uZZ5FSM9Ttw",
     "watchHistory": "HL",
     "watchLater": "WL"
    }
   },
   "statistics": {
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

















