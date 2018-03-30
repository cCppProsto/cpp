#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>

#include "channel.hpp"

/*
{
 "kind": "youtube#channelListResponse",
 "etag": "\"RmznBCICv9YtgWaaa_nWDIH1_GM/cZnF4vvOg72FSt8eEeDmBu9kZQI\"",
 "pageInfo": {
  "totalResults": 1,
  "resultsPerPage": 1
 },
  "items":
[
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

//------------------------------------------------------------------------------
static auto get_statistic_map(const QVariantMap &aMap)
{
  auto item = aMap["items"].toList().at(0);
  return item.toMap()["statistics"].toMap();
}
//------------------------------------------------------------------------------
static auto get_thumbnails_map(const QVariantMap &aMap)
{
  auto item = aMap["items"].toList().at(0);
  auto snippet = item.toMap()["snippet"].toMap();

  return snippet["thumbnails"].toMap();
}
//------------------------------------------------------------------------------
static void fill_ytStatistic(ytStatistic &aObj, const QVariantMap &aMap)
{
  aObj.commentCount           = aMap["commentCount"].toInt();
  aObj.subscriberCount        = aMap["subscriberCount"].toInt();
  aObj.viewCount              = aMap["viewCount"].toInt();
  aObj.videoCount             = aMap["videoCount"].toInt();
  aObj.hiddenSubscriberCount  = aMap["hiddenSubscriberCount"].toBool();
}
//------------------------------------------------------------------------------
static void fill_ytThumbs(ytThumbnails &aObj, const QVariantMap &aMap)
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
channel::channel(std::string aID, QObject *obj)
  :mId(aID)
{
  mpNetManager.reset(new QNetworkAccessManager(obj));
}
//------------------------------------------------------------------------------
channel::channel(channel &&aObj)
  : mIsLoaded(std::move(aObj.mIsLoaded))
   ,mIsThumbLoaded(std::move(aObj.mIsThumbLoaded))
   ,mId(std::move(aObj.mId))
   ,mStatistic(std::move(aObj.mStatistic))
   ,mThumbsInfo(std::move(aObj.mThumbsInfo))
   ,mThumbs(std::move(aObj.mThumbs))
   ,mpNetManager(std::move(aObj.mpNetManager))
{
}
//------------------------------------------------------------------------------
void channel::fetchData()
{
  QUrl url("https://www.googleapis.com/youtube/v3/channels/");

  QUrlQuery query;
  query.addQueryItem("id", QString(mId.c_str()));
  query.addQueryItem("key", "AIzaSyBQ1Azp81TRIgb68qR-Msc2S2ZrJzDvDUM");
  query.addQueryItem("part", "snippet,contentDetails,statistics");

  url.setQuery(query);

  qWarning() << url.toString();

  connect(mpNetManager.get(), SIGNAL(finished(QNetworkReply*)),
          this,               SLOT(fetch_result(QNetworkReply*)));

  mpNetManager.get()->get(QNetworkRequest(url));
}
//------------------------------------------------------------------------------
void channel::fetch_result(QNetworkReply *apReply)
{
  QString data = (QString) apReply->readAll();

  QJsonDocument jsonDoc    = QJsonDocument::fromJson(data.toUtf8());
  QJsonObject   jsonObject = jsonDoc.object();
  QVariantMap   vmap       = jsonObject.toVariantMap();

  if(!vmap.isEmpty())
  {
    fill_ytStatistic(mStatistic, get_statistic_map(vmap));
    fill_ytThumbs(mThumbsInfo,   get_thumbnails_map(vmap));
    mIsLoaded = true;

    QNetworkRequest request;
    auto url = QUrl(mThumbsInfo.high_url);
    request.setUrl(url);

    disconnect(mpNetManager.get(), SIGNAL(finished(QNetworkReply*)),
               this,               SLOT(fetch_result(QNetworkReply*)));

    connect(mpNetManager.get(), SIGNAL(finished(QNetworkReply*)),
            this,               SLOT(thumb_result(QNetworkReply*)));

    mpNetManager.get()->get(request);
  }
}
//------------------------------------------------------------------------------
void channel::thumb_result(QNetworkReply *apReply)
{
  auto e = apReply->error();

  if(e != QNetworkReply::NoError)
    return;

  auto res = apReply->readAll();

  if(res.size() > 0)
  {
    mThumbs.loadFromData(res);
    mIsThumbLoaded = true;
  }
}
//------------------------------------------------------------------------------
const QPixmap &channel::pixmap()const
{
  return mThumbs;
}
//------------------------------------------------------------------------------
const bool &channel::isLoaded()const
{
  return mIsLoaded;
}
//------------------------------------------------------------------------------
const bool &channel::thumbIsLoaded()const
{
  return mIsThumbLoaded;
}





















