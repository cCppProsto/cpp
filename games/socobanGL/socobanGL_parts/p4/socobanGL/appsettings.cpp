#include "appsettings.hpp"

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
}

void appSettings::save()
{
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


