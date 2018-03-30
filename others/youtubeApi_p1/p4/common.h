#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QPixmap>
#include <QNetworkReply>
#include <QNetworkAccessManager>

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


#endif // COMMON_H
