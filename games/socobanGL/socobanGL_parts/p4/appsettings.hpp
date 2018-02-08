#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP

#include <QString>

struct appSettings
{
  appSettings(const appSettings &) = delete;
  appSettings & operator=(const appSettings&) = delete;

  static appSettings &instance();

  void load();
  void save();

  QString  levelsPath() const;
  unsigned screenWidth() const;
  unsigned screenHeight() const;

private:
  appSettings();
  ~appSettings();

private:
  unsigned mScreenWidth{0};
  unsigned mScreenHeight{0};
};

#endif // APPSETTINGS_HPP
