#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // Criar um socket TCP/IP
    if (sockfd < 0) {
        std::cerr << "Erro ao criar o socket." << std::endl;
        return 1;
    }

    // Configurar o endereço para ligação
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(8080); // Porta 8080

    // Ligação do socket
    if (bind(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        std::cerr << "Erro ao ligar o socket." << std::endl;
        return 1;
    }

    // Configurar o socket para ouvir conexões
    if (listen(sockfd, 5) < 0) { // 5 é o tamanho da fila de conexões pendentes
        std::cerr << "Erro ao configurar o socket para ouvir conexões." << std::endl;
        return 1;
    }

    std::cout << "Socket configurado para ouvir conexões." << std::endl;

    // Aceitar uma conexão de entrada
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    int newsockfd = accept(sockfd, (struct sockaddr *) &clientAddr, &clientLen);
    if (newsockfd < 0) {
        std::cerr << "Erro ao aceitar a conexão." << std::endl;
        return 1;
    }

    std::cout << "Conexão aceita. Novo socket: " << newsockfd << std::endl;

    // Realizar operações com o novo socket...

    close(newsockfd); // Fechar o novo socket
    close(sockfd); // Fechar o socket de escuta

    return 0;
}
