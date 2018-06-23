#include <thread>
#include <mutex>
#include <fstream>
#include <vector>
#include <chrono>
#include <iostream>


#include <curl/curl.h>

#include "curl_downloader.hpp"
#include "curl_tool.hpp"

const unsigned THREAD_COUNT { 8 };


std::chrono::high_resolution_clock::time_point get_time()
{
  return std::chrono::high_resolution_clock::now();
}

unsigned diff_ms(std::chrono::high_resolution_clock::time_point t1,
                 std::chrono::high_resolution_clock::time_point t2)
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
}

unsigned diff_sec(std::chrono::high_resolution_clock::time_point t1,
                 std::chrono::high_resolution_clock::time_point t2)
{
  return std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count();
}

struct sCallback_data
{
  unsigned     partNumber;
  std::fstream *file;
  std::mutex   *pMutex;
};


size_t multithread_call_back(void *ptr,
                             size_t size,
                             size_t nmemb,
                             void *aData)
{
  sCallback_data *data = (sCallback_data *)aData;

  if(data->file->is_open())
  {
    data->pMutex->lock();
    data->file->write(reinterpret_cast<char*>(ptr), size * nmemb);
    data->pMutex->unlock();
  }
  return size * nmemb;
}


curl_downloader::curl_downloader()
{
}
//------------------------------------------------------------------------------
void curl_downloader::load(std::string aUrl)
{
  size_t file_size = curl_tool::instance().get_file_size(aUrl);
  if(file_size == 0)
    return;

  std::mutex mutex;

  unsigned part_size = file_size / THREAD_COUNT;

  auto download_func = [this, &mutex, &aUrl](
                              size_t        start
                             ,size_t        end
                             ,unsigned      partID
                             ,std::fstream *file)
  {
    std::string msRange{std::to_string(start) + "-" + std::to_string(end)};
    CURL        *curl{nullptr};

    sCallback_data data{partID, file, &mutex};

    //mutex.lock();
    // some actions
    //mutex.unlock();

    curl = curl_easy_init();
    if(curl)
    {
      curl_easy_setopt(curl, CURLOPT_URL,           aUrl.c_str());
      curl_easy_setopt(curl, CURLOPT_RANGE,         msRange.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEDATA,     (void*)(&data));
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, multithread_call_back);

      curl_easy_setopt(curl, CURLOPT_VERBOSE,        0L);
      curl_easy_setopt(curl, CURLOPT_HEADER,         0L);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

      curl_easy_perform(curl);

      // mutex.lock();
      // some actions
      // mutex.unlock();

      file->close();
      curl_easy_cleanup(curl);
    }
  };

  std::vector<std::thread>   threads;
  size_t start { 0 };
  size_t end   { part_size };

  std::vector<std::fstream> files;

  files.resize(THREAD_COUNT);
  threads.resize(THREAD_COUNT);

  for(unsigned i = 0; i < THREAD_COUNT; ++i)
  {
    start = i * part_size;
    end   = ((i+1) * part_size) - 1;
    if(i == THREAD_COUNT - 1)
      end = file_size;

    std::string path;
    path += std::to_string(i);
    files[i].open(path,   std::ios_base::in
                        | std::ios_base::out
                        | std::ios_base::binary
                        | std::ios_base::trunc);

    threads[i] = std::thread(download_func,
                             start,
                             end,
                             i,
                             &files[i]);
  }

  auto t1 = get_time();
  for(unsigned i = 0; i < THREAD_COUNT; ++i)
  {
    threads[i].join();
  }
  auto t2 = get_time();

  auto diff = diff_sec(t1,t2);
  std::cout << file_size
            << " bytes) "
            << "thread - "
            << THREAD_COUNT
            << " : load time - "
            << diff
            << " seconds"
            << std::endl;

  std::ofstream main_file("out.mp4", std::ios_base::binary);
  for (unsigned i = 0; i < THREAD_COUNT; ++i)
  {
    std::ifstream file(std::to_string(i));
    if(file.is_open())
    {
      main_file << file.rdbuf();
      file.close();
    }
  }
  main_file.close();
}



