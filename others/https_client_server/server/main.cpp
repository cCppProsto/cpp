#include <iostream>
#include <experimental/filesystem>

#include "server.hpp"

using namespace std;

namespace fs = std::experimental::filesystem;

// SSL connection tutorial
// http://h41379.www4.hpe.com/doc/83final/ba554_90007/ch04s03.html

// generate certificate
// sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout selfsigned.key -out selfsigned.crt


// https://aws.amazon.com/ru/getting-started/tutorials/get-a-domain/
// https://aws.amazon.com/ru/getting-started/tutorials/
// https://aws.amazon.com/ru/getting-started/tutorials/launch-a-virtual-machine/
// https://aws.amazon.com/ru/getting-started/tutorials/get-a-domain/
// https://aws.amazon.com/ru/websites/

// sudo ssh -i LightsailDefaultPrivateKey-eu-west-3.pem ubuntu@35.180.105.138
// sudo scp -i LightsailDefaultPrivateKey-eu-west-3.pem certificates/selfsigned.crt   ubuntu@35.180.105.138:/home/ubuntu

// ./server 443 > log.log & disown

int main(int argc, char **argv)
{
  int port { 11000 };
  if(argc >= 2)
    port = std::stoi(argv[1]);

  server serv(port);

  fs::path path_cert = fs::current_path() / "certificates" / "selfsigned.crt";
  fs::path path_key  = fs::current_path() / "certificates" / "selfsigned.key";

  serv.setCertPath(path_cert.string());
  serv.setKeyPath(path_key.string());

  if(!serv.start())
    std::cerr << "server can not be start, see above" << std::endl;

  return 0;
}
