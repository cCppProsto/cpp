#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include <memory>

#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class channel : public QObject
{
  Q_OBJECT
public:
  channel(std::string aID, QObject *obj = nullptr);

  void fetchData();

private slots:
  void fetch_result(QNetworkReply*);


private:
  std::string mId;
  std::unique_ptr<QNetworkAccessManager> mpNetManager{nullptr};
};

#endif // CHANNEL_HPP
