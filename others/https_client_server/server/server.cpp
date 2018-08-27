#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
#include <experimental/filesystem>

#include "server.hpp"
#include "../common/http_request.hpp"


// http://h41379.www4.hpe.com/doc/83final/ba554_90007/ch04s03.html#
namespace fs = std::experimental::filesystem;


//------------------------------------------------------------------------------
static std::string get_date_time()
{
  char buffer[100] = { 0 };
  time_t curr_time;
  tm    *curr_tm;
  time(&curr_time);
  curr_tm = localtime(&curr_time);
  strftime(buffer, 100, "%T %d.%m.%Y", curr_tm);
  return std::string(buffer);
}
//------------------------------------------------------------------------------
static void *get_in_addr(sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
    return &(((sockaddr_in*)sa)->sin_addr);

  return &(((sockaddr_in6*)sa)->sin6_addr);
}
//------------------------------------------------------------------------------
static std::string get_ip_addr(const sockaddr_in &aClientData)
{
  char ip[INET6_ADDRSTRLEN] = { 0 };
  inet_ntop(aClientData.sin_family, get_in_addr((sockaddr *)&aClientData), ip, sizeof ip);
  return std::string(ip);
}

//------------------------------------------------------------------------------
server::server(int aPort)
  :m_port(aPort)
{
}
//------------------------------------------------------------------------------
server::~server()
{
  if(mp_ssl_context != nullptr)
    SSL_CTX_free(mp_ssl_context);
  mp_ssl_context = nullptr;
}
//------------------------------------------------------------------------------
bool server::start()
{
  std::ifstream f_html_file;
  fs::path path_html_file = fs::current_path() / "html_data" / "index.html";
  f_html_file.open(path_html_file.c_str(), std::ios::binary  | std::ios::ate);

  if(!f_html_file.is_open())
  {
    std::cerr << "html file did not opened! path - " << path_html_file.c_str() << std::endl;
    return false;
  }

  m_html_data.reserve(f_html_file.tellg());
  f_html_file.seekg(0, std::ios::beg);
  m_html_data.assign((std::istreambuf_iterator<char>(f_html_file)), std::istreambuf_iterator<char>());
  f_html_file.close();

  std::ifstream f_icon_file;
  fs::path path_icon_file = fs::current_path() / "icons" / "favicon.png";
  f_icon_file.open(path_icon_file.c_str(), std::ios::binary | std::ios::ate);

  if(!f_icon_file.is_open())
  {
    std::cerr << "favicon file did not opened! path - " << path_icon_file.c_str() << std::endl;
  }

  std::streamsize size = f_icon_file.tellg();
  m_fav_icon_buffer.resize(size);
  f_icon_file.seekg(0, std::ios::beg);
  if(!f_icon_file.read(m_fav_icon_buffer.data(), size))
  {
    std::cerr << "favicon read error!" << std::endl;
  }
  f_icon_file.close();

  if(!_ssl_init())
  {
    std::cerr << "ssl init error" << std::endl;
    return false;
  }

  if( !_socket_init())
  {
    std::cerr << "socket init error" << std::endl;
    return false;
  }

  std::cout << "server: was started, port:" << m_port << std::endl;
  m_start_date_time = get_date_time();

  while(1)
  {
    int         sock_cli;
    sockaddr_in sa_cli;
    socklen_t   client_len = sizeof(sa_cli);

    sock_cli = accept(m_socket, (sockaddr*)&sa_cli, &client_len);
    if(sock_cli == -1)
    {
      std::cerr << "accept error:" << m_port << std::endl;
      continue;
    }

    std::string ip = get_ip_addr(sa_cli);
    _client_processing(sock_cli, ip);
  }

  return true;
}
//------------------------------------------------------------------------------
void server::setCertPath(std::string aPath)
{
  m_certificate_path = aPath;
}
//------------------------------------------------------------------------------
void server::setKeyPath(std::string aPath)
{
  m_key_path = aPath;
}
//------------------------------------------------------------------------------
void server::setPathForCA(std::string aPath)
{
  m_ca_path = aPath;
}
//------------------------------------------------------------------------------
bool server::_ssl_init()
{
  SSL_library_init();

  // load all error messages
  SSL_load_error_strings();

  // create new server-method instance
  mp_ssl_method = const_cast<SSL_METHOD*>(TLSv1_2_server_method());

  // create new context from method
  mp_ssl_context = SSL_CTX_new(mp_ssl_method);

  if ( mp_ssl_context == NULL )
  {
    ERR_print_errors_fp(stderr);
    return false;
  }

  // set the local certificate from CertFile
  if ( SSL_CTX_use_certificate_file(mp_ssl_context, m_certificate_path.c_str(), SSL_FILETYPE_PEM) <= 0 )
  {
    ERR_print_errors_fp(stderr);
    return false;
  }
  // set the private key from KeyFile (may be the same as CertFile)
  if ( SSL_CTX_use_PrivateKey_file(mp_ssl_context, m_key_path.c_str(), SSL_FILETYPE_PEM) <= 0 )
  {
    ERR_print_errors_fp(stderr);
    return false;
  }

  // verify private key
  if ( !SSL_CTX_check_private_key(mp_ssl_context) )
  {
    ERR_print_errors_fp(stderr);
    return false;
  }

  if(m_ca_path.size() > 0)
  {
    if(SSL_CTX_load_verify_locations(mp_ssl_context, m_ca_path.c_str(), NULL) == 0)
    {
      ERR_print_errors_fp(stderr);
      return false;
    }
  }

  return true;
}
//------------------------------------------------------------------------------
bool server::_socket_init()
{
  m_socket = socket(PF_INET, SOCK_STREAM, 0);

  if(m_socket == -1)
  {
    std::cerr << "Can't create socket" << std::endl;
    return false;
  }

  sockaddr_in sa_serv;
  memset(&sa_serv, 0, sizeof(sa_serv));
  sa_serv.sin_family      = AF_INET;
  sa_serv.sin_addr.s_addr = INADDR_ANY;
  sa_serv.sin_port        = htons(m_port);

  if(bind(m_socket, (sockaddr*)&sa_serv, sizeof(sa_serv)) !=0 )
  {
    std::cerr << "can't bind port " << m_port << std::endl;
    return false;
  }

  if ( listen(m_socket, 1000) != 0 )
  {
    std::cerr << "Can't configure listening port" << std::endl;
    return false;
  }
  return true;
}
//------------------------------------------------------------------------------
void server::_client_processing(int aSocket, std::string aIp)
{
  SSL *ssl;
  ssl = SSL_new(mp_ssl_context);    // get new SSL state with context
  SSL_set_fd(ssl, aSocket);         // set connection socket to SSL state

  // service connection
  char buffer[1024 * 16] = { 0 };
  int  read_bytes { 0 };

  if ( SSL_accept(ssl) == -1 )      // do SSL-protocol accept
  {
    ERR_print_errors_fp(stderr);
    SSL_free(ssl);                  // release SSL state
    close(aSocket);
    return;
  }

  read_bytes = SSL_read(ssl, buffer, sizeof(buffer));  // get request

  if(read_bytes <= 0)
  {
    SSL_free(ssl);                  // release SSL state
    close(aSocket);
    return;
  }
  buffer[read_bytes] = '\0';

  http_request request;
  request.parse(buffer);

  std::cout << "connection from(" << aIp << ")"
            << " request uri \"" << request.uri() << "\"" << std::endl;

  if(request.type() != http_request::eType::GET)
  {
    std::cout << "unknown type of request. Not support." << std::endl;
    return;
  }

  ++m_get_request_count;

  switch (request.uri().length())
  {
    case 1: // "/"
    {
      if(request.uri() == "/")
      {
        std::stringstream response;
        response << "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nContent-Type: text/html\r\nContent-Length: " << m_html_data.size() << "\r\n\r\n";

        int sended = 0;
        // send status OK
        sended = SSL_write(ssl, response.str().c_str(), response.str().length());

        if(sended > 0)
        {
          // send index.html
          sended = SSL_write(ssl, m_html_data.data(), m_html_data.size());
        }
      }
      break;
    }
    case 12: // "/favicon.ico"
    {
      if(request.uri() == "/favicon.ico")
      {
        std::stringstream response;
        response << "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nContent-Type: image/png\r\nContent-Length: " << m_fav_icon_buffer.size() << "\r\n\r\n";

        int sended = 0;
        // send status OK
        sended = SSL_write(ssl, response.str().c_str(), response.str().length());
        //std::cout << "HTTP/1.1 200 OK - was send" << std::endl;

        if(sended > 0)
        {
          // send index.html
          sended = SSL_write(ssl, m_fav_icon_buffer.data(), m_fav_icon_buffer.size());
          //std::cout << " sended " << sended << " bytes" << std::endl;
        }
        break;
      }
    }
    case 38: // "/how_many_requests_were_from_beginning"
    {
      if(request.uri() == "/how_many_requests_were_from_beginning")
      {
        std::stringstream response;

        response << "server was started   : " << m_start_date_time   << "<br>"
                 << "count of GET request : " << m_get_request_count << "<br>";

        std::stringstream ok_response;
        ok_response << "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nContent-Type: text/html\r\nContent-Length: " << response.str().size() << "\r\n\r\n";

        int sended = 0;
        sended = SSL_write(ssl, ok_response.str().c_str(), ok_response.str().length());
        if(sended > 0)
          sended = SSL_write(ssl, response.str().data(), response.str().size());
      }
      break;
    }
  }
}


























