#include <curl/curl.h>

#include "curl_tool.hpp"


curl_tool &curl_tool::instance()
{
  static curl_tool res;
  return res;
}
//------------------------------------------------------------------------------
curl_tool::curl_tool()
{
  if(curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK)
  {
    m_is_inited = true;
  }
}
//------------------------------------------------------------------------------
curl_tool::~curl_tool()
{
  if(m_is_inited)
  {
    curl_global_cleanup();
  }
}
//------------------------------------------------------------------------------
size_t curl_tool::get_file_size(const std::string aURL)
{
  if(!m_is_inited)
    return 0;

  CURL *curl        { nullptr };
  CURLcode res_code { CURLE_OK };

  curl = curl_easy_init();
  if(!curl)
    return 0;

  curl_easy_setopt(curl, CURLOPT_URL,             aURL.c_str());
  curl_easy_setopt(curl, CURLOPT_NOBODY,          1L);
  curl_easy_setopt(curl, CURLOPT_HEADER,          0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,  0L);

  res_code = curl_easy_perform(curl);
  double file_size = 0.;

  if(res_code == CURLE_OK)
  {
    res_code = curl_easy_getinfo(curl,
                                 CURLINFO_CONTENT_LENGTH_DOWNLOAD,
                                 &file_size);
    if(res_code == CURLE_OK)
      return (size_t)file_size;
  }

  return 0;
}


