#include <QDebug>

#include "channel.hpp"


channel::channel(std::string aID, QObject *obj)
  :mId(aID)
{
  mpNetManager.reset(new QNetworkAccessManager(obj));
}

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

void channel::fetch_result(QNetworkReply *apReply)
{
  QString res = QString(apReply->readAll());
  qWarning() << res;
}
