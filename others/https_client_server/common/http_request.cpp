#include <sstream>
#include "http_request.hpp"

//------------------------------------------------------------------------------
http_request::http_request()
{

}
//------------------------------------------------------------------------------
void http_request::parse(const char *apDataStr)
{
  std::istringstream iss(apDataStr);

  std::string line;

  std::getline(iss, line);

  _parse_request_line(line);

  std::string str;
  while (std::getline(iss, line))
  {
    std::istringstream iss_line(line);
    iss_line >> str;
  }
  str = "";
}
//------------------------------------------------------------------------------
void http_request::_parse_request_line(std::string &aStr)
{
  m_type = eType::Unknown;

  std::istringstream iss(aStr);
  std::string type;

  iss >> type;

  switch (type.length())
  {
    case 3: // GET
    {
      if(type == "GET")
        m_type = eType::GET;
      break;
    }
  }
  iss >> m_uri;
}
//------------------------------------------------------------------------------
const http_request::eType &http_request::type()const
{
  return m_type;
}
//------------------------------------------------------------------------------
const std::string &http_request::uri() const
{
  return m_uri;
}
