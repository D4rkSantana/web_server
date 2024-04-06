#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
  // Defina a porta
  const int port = 55000;

  // Crie um socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// o que é socket? >> ponto de comunicação bi derecional (isso é uma função)

  if (sockfd < 0) {
    std::cerr << "Erro ao criar socket: " << hstrerror(errno) << std::endl;
    return 1;
  }

  // Bind do socket à porta
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
//	addr.sin_addr.s_addr = INADDR_ANY;
//	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

  if (bind(sockfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
    std::cerr << "Erro ao fazer bind: " << hstrerror(errno) << std::endl;
    return 1;
  }

  // Listen no socket
  if (listen(sockfd, 5) < 0) {
    std::cerr << "Erro ao listen: " << hstrerror(errno) << std::endl;
    return 1;
  }

  while (true) {
    // Aceite uma nova conexão
    int clientfd = accept(sockfd, nullptr, nullptr);

    if (clientfd < 0) {
      std::cerr << "Erro ao aceitar conexão: " << hstrerror(errno) << std::endl;
      continue;
    }else{
		std::cout << "Aguardando Requisições na porta: ->>  " << port << std::endl;
	}

    // Receba a requisição
    char request[1024];
    int bytes_received = recv(clientfd, request, sizeof(request), 0);
    if (bytes_received < 0) {
      std::cerr << "Erro ao receber requisição: " << hstrerror(errno) << std::endl;
      close(clientfd);
      continue;
    }

    std::cout << "Conexão recedida com sucesso ->>  " << request << "\n\n" << std::endl;

    // Crie a resposta HTML
    std::string response = "<!DOCTYPE html>";
    response += "<html><head><title>Resposta do Servidor</title></head>";
    response += "<body>";
    response += "<h1>Aqui está a sua resposta!</h1>";
    response += "<p>Você enviou a seguinte requisição:</p>";
    response += "<pre>";
    response += request;
    response += "</pre>";
    response += "</body></html>";

    // Defina o tipo de conteúdo
    setsockopt(clientfd, IPPROTO_TCP, TCP_CONTENT_TYPE, "text/html", strlen("text/html"));

    // Envie a resposta
    int bytes_sent = send(clientfd, response.c_str(), response.length(), 0);
    if (bytes_sent < 0) {
      std::cerr << "Erro ao enviar resposta: " << hstrerror(errno) << std::endl;
      close(clientfd);
      continue;
    }

    // Feche a conexão
    close(clientfd);
  }
  // Feche o socket
  close(sockfd);
  return 0;
}
