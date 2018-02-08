#include "appsettings.hpp"

#include <QDirIterator>

static const QString levels_path = "levels/";

appSettings::appSettings()
{
  load();
}

appSettings::~appSettings()
{
  save();
}

appSettings &appSettings::instance()
{
  static appSettings res;
  return res;
}

void appSettings::load()
{
  // load app settings
  // ...

  // load player info
  // ...

  // load levels info

  mAvailableLevels.clear();

  QDirIterator it(levels_path);

  while (it.hasNext())
  {
    it.next();
    QFileInfo info(it.fileInfo());
    if(info.completeSuffix() == "lvl")
      mAvailableLevels.push_back({info.baseName().toInt(), true});
  }

  std::sort(mAvailableLevels.begin(), mAvailableLevels.end(),
            [](const auto &a, const auto &b) -> bool
            {
              return a.first < b.first;
            });

  //if(mAvailableLevels.size() == 0)
  //  return;

  //mAvailableLevels[0].second = true;
}

void appSettings::save()
{
}

QString  appSettings::levelsPath() const
{
  return levels_path;
}

unsigned appSettings::screenWidth() const
{
  static unsigned res{800};
  return res;
}
unsigned appSettings::screenHeight() const
{
  static unsigned res{600};
  return res;
}
const std::vector<std::pair<int, bool>> &appSettings::availablesLevels()
{
  return mAvailableLevels;
}


























