#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <memory>

#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "common.h"

class channel : public QObject
{
  Q_OBJECT
public:
  channel(std::string aID, QObject *obj = nullptr);
  channel(channel &&);

  void fetchData();

  const QPixmap &pixmap()const;
  const bool &isLoaded()const;
  const bool &thumbIsLoaded()const;

private slots:
  void fetch_result(QNetworkReply*);
  void thumb_result(QNetworkReply*);

private:
  bool         mIsLoaded{false};
  bool         mIsThumbLoaded{false};
  std::string  mId;
  ytStatistic  mStatistic;
  ytThumbnails mThumbsInfo;
  QPixmap      mThumbs;

  std::unique_ptr<QNetworkAccessManager> mpNetManager{nullptr};
};

#endif // CHANNEL_HPP
