#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
  // Defina o endereço e a porta do servidor
  const char* host = "localhost";
  const int port = 80;

  // Crie um socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "Erro ao criar socket: " << strerror(errno) << std::endl;
    return 1;
  }

  // Conecte-se ao servidor
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  if (inet_pton(AF_INET, host, &addr.sin_addr) <= 0) {
    std::cerr << "Erro ao converter endereço: " << strerror(errno) << std::endl;
    return 1;
  }
  if (connect(sockfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
    std::cerr << "Erro ao conectar: " << strerror(errno) << std::endl;
    return 1;
  }

  // Envie uma requisição
  const char* request = "GET / HTTP/1.1\n\n";
  if (send(sockfd, request, strlen(request), 0) < 0) {
    std::cerr << "Erro ao enviar requisição: " << strerror(errno) << std::endl;
    return 1;
  }

  // Receba a resposta
  char response[1024];
  int bytes_received = recv(sockfd, response, sizeof(response), 0);
  if (bytes_received < 0) {
    std::cerr << "Erro ao receber resposta: " << strerror(errno) << std::endl;
    return 1;
  }

  // Imprima a resposta
  std::cout << response << std::endl;

  // Feche a conexão
  close(sockfd);

  return 0;
}
