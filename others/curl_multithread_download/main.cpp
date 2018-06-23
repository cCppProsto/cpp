#include <iostream>
#include "curl_downloader.hpp"
using namespace std;

int main()
{
  curl_downloader dwnl;
  //std::string url {"https://www.sample-videos.com/video/mp4/720/big_buck_bunny_720p_30mb.mp4"};
  //std::string url {"https://www.sample-videos.com/video/mp4/720/big_buck_bunny_720p_10mb.mp4"};
  std::string url {"https://www.sample-videos.com/video/mp4/720/big_buck_bunny_720p_5mb.mp4"};
  dwnl.load(url);
  // 31491130
  return 0;
}
