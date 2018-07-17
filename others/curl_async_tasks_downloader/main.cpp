#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>
#include <future>
#include <queue>
#include <experimental/filesystem>
#include <functional>

#include <curl/curl.h>

using namespace std;
namespace fs = std::experimental::filesystem;


//std::string   file_url = "https://www.sample-videos.com/video/mkv/240/big_buck_bunny_240p_30mb.mkv";
std::string   file_url = "https://download.applied-maths.com/sites/default/files/download/database/BandScoring01.bnbk";
size_t        chunk_size  = 1024*128; // 128KB
std::fstream  file;

typedef size_t(*curl_write_fptr)(void*, size_t, size_t, void*);

struct sCallBackData
{
  char  *mp_buffer { nullptr };
  size_t m_index   { 0 };
};


namespace curl_ns
{
  std::vector<std::pair<bool,CURL*> > g_curl_handles;
  size_t m_used_h { 0 };

  //----------------------------------------------------------------------------
  void init()
  {
    if (curl_global_init(CURL_GLOBAL_DEFAULT) == CURLE_OK)
      std::cout << "curl inited!" << std::endl;
  }
  //----------------------------------------------------------------------------
  void clean()
  {
    for(auto handles : g_curl_handles)
      curl_easy_cleanup(handles.second);

    curl_global_cleanup();
  }
  //----------------------------------------------------------------------------
  CURL *getHandle()
  {
    size_t index { 0 };

    if(m_used_h == g_curl_handles.size())
    {
      std::pair<bool, CURL*> tmp;
      tmp.first = true;
      tmp.second = curl_easy_init();

      g_curl_handles.push_back(tmp);
      index = g_curl_handles.size() - 1;
      m_used_h++;
    }
    else
    {
      for(size_t i = 0; i < g_curl_handles.size(); ++i)
      {
        if(g_curl_handles[i].first == false)
        {
          index = i;
          g_curl_handles[i].first = true;
          m_used_h++;
          break;
        }
      }
    }
    return g_curl_handles[index].second;
  }
  //----------------------------------------------------------------------------
  void releaseHandle(CURL *apHandle)
  {
    for(size_t i = 0; i < g_curl_handles.size(); ++i)
    {
      if(g_curl_handles[i].second == apHandle)
      {
        g_curl_handles[i].first = false;
        m_used_h--;
        break;
      }
    }
  }
  //----------------------------------------------------------------------------
  size_t get_file_size(const std::string aFileUrl)
  {
    CURL     *curl = curl_easy_init();
    CURLcode  res;

    curl_easy_setopt(curl, CURLOPT_URL, aFileUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_NOBODY,         1L);
    curl_easy_setopt(curl, CURLOPT_HEADER,         0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    res = curl_easy_perform(curl);
    double filesize = 0.0;

    if (res == CURLE_OK)
    {
      res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &filesize);
      if (res == CURLE_OK)
      {
        curl_easy_cleanup(curl);
        return (size_t)filesize;
      }
    }
    curl_easy_cleanup(curl);
    return 0;
  }
}

namespace download_ns
{
  bool download(std::string aRanges, size_t aPartID)
  {
    static std::mutex m;

    //-- curl callback function ------------------------------------------------
    auto write_func = [](void *ptr, size_t size, size_t nmemb, void *aData)
    {
      sCallBackData *data = (sCallBackData *)aData;
      size_t length = size * nmemb;
      std::memcpy(&data->mp_buffer[data->m_index], ptr, length);
      data->m_index += length;
      return length;
    };

    sCallBackData data;
    data.mp_buffer = new char[chunk_size];
    data.m_index = 0;

    m.lock();
      CURL *handle = curl_ns::getHandle();

      curl_easy_setopt(handle, CURLOPT_RANGE,         aRanges.c_str());
      curl_easy_setopt(handle, CURLOPT_URL,           file_url.c_str());
      curl_easy_setopt(handle, CURLOPT_WRITEDATA,     (void*)(&data));
      curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, static_cast<curl_write_fptr>(write_func));

      curl_easy_setopt(handle, CURLOPT_VERBOSE,        0L);
      curl_easy_setopt(handle, CURLOPT_HEADER,         0L);
      curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
      curl_easy_setopt(handle, CURLOPT_TIMEOUT, 100L);
    m.unlock();

    CURLcode res = curl_easy_perform(handle); // downloading ...
    double speed { 0. };
    double time  { 0. };
    curl_easy_getinfo(handle, CURLINFO_SPEED_DOWNLOAD, &speed);
    curl_easy_getinfo(handle, CURLINFO_TOTAL_TIME,     &time);

    if(res == CURLE_OK)
    {
      m.lock();
      size_t pos = aPartID * chunk_size;

      if(pos == 0)
        pos = 0;
      file.seekp(pos);
      file.write(data.mp_buffer, data.m_index);

      std::cout << "curl_handle("
                << handle
                << ") "
                << "(th_id:"
                << this_thread::get_id()
                << ") "
                << "ranges("
                << aRanges
                << ") completed" << std::endl;
      m.unlock();
    }
    else
    {
      std::cout << "curl error " << res << std::endl;
    }

    m.lock();
    curl_ns::releaseHandle(handle);
    m.unlock();

    delete [] data.mp_buffer;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    if(res != CURLE_OK)
      download(aRanges, aPartID);

    return true;
  }
}

int main()
{
  std::cout << "main thread id " << this_thread::get_id() << std::endl;

  curl_ns::init();

  size_t file_size = curl_ns::get_file_size(file_url);

  std::string hash = std::to_string(std::hash<std::string>()(file_url));
  fs::path    path = fs::current_path() / hash;
  fs::create_directories(path);

  path = path / hash;


  bool is_exist = fs::exists(path);
  if(!is_exist)
  {
    file.open(path.c_str(), std::ios::binary | std::ios::out | std::ios::in | std::ios::trunc);
    fs::resize_file(path.c_str(), file_size);
  }
  else
    file.open(path.c_str(), std::ios::binary | std::ios::out | std::ios::in);

  size_t chunk_count = (file_size / chunk_size) + 1;

  std::queue<std::future<bool>> task_queue;

  size_t start { 0 };
  size_t end   { 0 };
  std::string range;

  typedef std::chrono::high_resolution_clock::time_point TimeVar;

  TimeVar t1 = std::chrono::high_resolution_clock::now();
  for(unsigned i = 0; i < chunk_count; ++i)
  {
    start = i * chunk_size;
    if((i + 1) == chunk_count)
      end = start + (file_size - start);
    else
      end = (start + chunk_size) - 1;
    range = std::to_string(start) + "-" + std::to_string(end);
    task_queue.push(std::async(download_ns::download, range, i));
    //task_queue.push(std::async(std::launch::async, download_ns::download, range, i));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  std::cout << "-----------------------------------" << std::endl;

  while(!task_queue.empty())
  {
    task_queue.front().wait();
    task_queue.pop();
  }
  TimeVar t2 = std::chrono::high_resolution_clock::now();
  unsigned mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  std::cout << mili  << " miliseconds" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;

  file.close();

  curl_ns::clean();

  return 0;
}
