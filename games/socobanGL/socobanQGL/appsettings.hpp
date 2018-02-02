#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP

#include <QString>
#include <QGLWidget>
#include <vector>

struct appSettings
{
  enum class eTexturesID
  {
    Wall
   ,Player
   ,Box
   ,BoxGoal
   ,Goal
   ,End
  };

  appSettings(const appSettings &) = delete;
  appSettings & operator=(const appSettings&) = delete;

  static appSettings &instance();

  void load();
  void save();

  void setQGLWidget(QGLWidget &);

  QString  levelsPath() const;
  unsigned screenWidth() const;
  unsigned screenHeight() const;

  const std::vector<std::pair<int, bool>> &availablesLevels();

  unsigned int textureID(eTexturesID);

private:
  void _load_texture();

private:
  appSettings();
  ~appSettings();

private:
  unsigned mScreenWidth{0};
  unsigned mScreenHeight{0};

  QGLWidget *mpGLContext{nullptr};

  std::vector<std::pair<int, bool>> mAvailableLevels;
};

#endif // APPSETTINGS_HPP
