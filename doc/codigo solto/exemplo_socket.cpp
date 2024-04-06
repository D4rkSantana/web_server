#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

int main() {
    int server_socket;
    struct sockaddr_in server_address;

    // Criação do socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Falha ao criar o socket" << std::endl;
        return EXIT_FAILURE;
    }

    // Configuração do endereço do servidor
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind do socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Falha no bind" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Socket criado e vinculado na porta " << PORT << std::endl;

    close(server_socket);
    return 0;
}
