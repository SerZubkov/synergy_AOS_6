#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main()
{
  int sock = 0;
  struct sockaddr_in serv_addr;
  char buffer[1024] = {0};

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    std::cout << "Ошибка создания сокета!" << std::endl;
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  // Конвертируем IPv4 и IPv6 адреса из текста в бинарную форму
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
  {
    std::cout << "Неверный адрес/ адрес не поддерживается" << std::endl;
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    std::cout << "Ошибка коннекта!" << std::endl;
    return -1;
  }

  std::cout << "Введите текст, чтобы отправить запрос: ";
  std::string socketName;
  std::getline(std::cin, socketName);
  send(sock, socketName.c_str(), socketName.length(), 0);

  close(sock);
  return 0;
}
