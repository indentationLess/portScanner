#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

bool is_port_open(const std::string &ip, int port) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "Socket creation failed: " << strerror(errno) << std::endl;
    return false;
  }

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) {
    close(sockfd);
    return true;
  }

  close(sockfd);
  return false;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <ip> <port_range>" << std::endl;
    return 1;
  }

  std::string ip = argv[1];
  int port_range = std::stoi(argv[2]);

  std::cout << "Scanning ports for " << ip << "..." << std::endl;

  for (int port = 1; port <= port_range; ++port) {
    if (is_port_open(ip, port)) {
      std::cout << "Port " << port << " is open" << std::endl;
    }
  }

  std::cout << "Scan complete" << std::endl;
  return 0;
}
