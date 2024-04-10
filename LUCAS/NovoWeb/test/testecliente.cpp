#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

const char* SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 5800;
const char* MESSAGE = "Olá, servidor!";

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Criar socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "Erro ao criar socket" << std::endl;
        return 1;
    }

    // Configurar endereço do servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        std::cerr << "Endereço de servidor inválido" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Conectar ao servidor
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Erro ao conectar ao servidor" << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Conectado ao servidor" << std::endl;

    // Enviar mensagem para o servidor
    if (send(clientSocket, MESSAGE, strlen(MESSAGE), 0) == -1) {
        std::cerr << "Erro ao enviar mensagem para o servidor" << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Mensagem enviada para o servidor: " << MESSAGE << std::endl;

    // Receber resposta do servidor
    char buffer[1024] = {0};
    int bytesReceived;
    if ((bytesReceived = recv(clientSocket, buffer, 1024, 0)) == -1) {
        std::cerr << "Erro ao receber resposta do servidor" << std::endl;
        close(clientSocket);
        return 1;
    }

    buffer[bytesReceived] = '\0';
    std::cout << "Resposta do servidor: " << buffer << std::endl;

    // Fechar socket
    close(clientSocket);

    return 0;
}
