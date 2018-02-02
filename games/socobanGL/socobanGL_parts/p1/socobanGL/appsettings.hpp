#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP


struct appSettings
{
  appSettings(const appSettings &) = delete;
  appSettings & operator=(const appSettings&) = delete;

  static appSettings &instance();

  void load();
  void save();

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
