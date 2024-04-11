#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
  const char *socket_path = "/tmp/my_socket";
  int socket_fd;
  struct sockaddr_un server_addr;

  socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (socket_fd == -1)
  {
    perror("Ошибка создания сокета!");
    return 1;
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, socket_path, sizeof(server_addr.sun_path) - 1);

  if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
  {
    perror("Ошибка соединения!");
    return 1;
  }

  std::string socketName;
  std::cout << "Введите текст, чтобы отправить запрос: ";
  std::getline(std::cin, socketName);
  write(socket_fd, socketName.c_str(), socketName.size());

  close(socket_fd);
  return 0;
}
