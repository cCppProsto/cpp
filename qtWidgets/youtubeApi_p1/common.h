#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QNetworkReply>

struct ytStatistic
{
  unsigned int viewCount;
  unsigned int commentCount;
  unsigned int subscriberCount;
  bool         hiddenSubscriberCount;
  unsigned int videoCount;
};

struct ytThumbnails
{
  int default_width;
  int default_height;
  int medium_width;
  int medium_height;
  int high_width;
  int high_height;

  QString default_url;
  QString medium_url;
  QString high_url;
};

struct ytChannel
{
  bool          isLoaded{false};
  QNetworkReply *pNetworkReply;
  QString       id;
  ytStatistic   statistic;
  ytThumbnails  thumbs;
};


#endif // COMMON_H
