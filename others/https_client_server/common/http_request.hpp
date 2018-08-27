#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>


// GET /favicon.ico HTTP

class http_request
{
public:
  enum class eType
  {
    Unknown = 0
    // The GET method is used to retrieve information from the given server
    // using a given URI. Requests using GET should only retrieve data and
    // should have no other effect on the data.
    ,GET
  };

public:
  http_request();

  void parse(const char*);

  const eType       &type() const;
  const std::string &uri()  const;

private:
  void _parse_request_line(std::string &);

private:
  eType       m_type  { eType::Unknown };
  std::string m_uri;

};

#endif // HTTP_REQUEST_HPP
