#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP

#include <QString>
#include <vector>

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

  const std::vector<std::pair<int, bool>> &availablesLevels();

private:
  appSettings();
  ~appSettings();

private:
  unsigned mScreenWidth{0};
  unsigned mScreenHeight{0};

  std::vector<std::pair<int, bool>> mAvailableLevels;
};

#endif // APPSETTINGS_HPP
