#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Criação do socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Erro ao criar o socket" << std::endl;
        return 1;
    }

    // Configuração do endereço para bind
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4000); // Porta 8080
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Erro no bind" << std::endl;
        return 1;
    }

    // Listen
    if (listen(serverSocket, 5) == -1) { // Máximo de 5 conexões pendentes
        std::cerr << "Erro no listen" << std::endl;
        return 1;
    }

    std::cout << "Servidor aguardando conexões..." << std::endl;

    // Aguarda conexões
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    // Cria o socket do servidor, faz o bind e inicia o listen

while (true) {
    // Aceita conexão de um cliente
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1) {
        std::cerr << "Erro ao aceitar conexão do cliente" << std::endl;
        continue;
    }

    // Lê dados do cliente
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1) {
        std::cerr << "Erro ao receber dados do cliente" << std::endl;
        close(clientSocket);
        continue;
    }

    // Exibe os dados recebidos
    std::cout << "Dados recebidos do cliente: " << std::string(buffer, bytesReceived) << std::endl;

    // Enviar resposta ao cliente
    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Olá, mundo!</h1></body></html>";
    int bytesSent = send(clientSocket, response.c_str(), response.length(), 0);
    if (bytesSent == -1) {
        std::cerr << "Erro ao enviar resposta ao cliente" << std::endl;
    }

    // Fecha o socket do cliente
    close(clientSocket);
}

// Fecha o socket do servidor
close(serverSocket);



    
    return 0;
}
