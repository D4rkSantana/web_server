#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Erro ao criar soquete" << std::endl;
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Erro ao fazer bind" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Servidor escutando na porta 8080" << std::endl;

    listen(sockfd, 5);

    int client_sockfd = accept(sockfd, nullptr, nullptr);
    if (client_sockfd < 0) {
        std::cerr << "Erro ao aceitar conexão" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Cliente conectado" << std::endl;

    // Faça alguma coisa com o soquete do cliente...

    close(client_sockfd);
    close(sockfd);

    return 0;
}
