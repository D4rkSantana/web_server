#include <iostream>
#include <fstream>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>

// Função para ler o conteúdo de um arquivo e codificá-lo em base64
std::string readFileAndEncodeBase64(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return "";
    }

    // Lê o conteúdo do arquivo em um vetor de bytes
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});

    // Codifica o conteúdo do vetor em base64
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string encoded;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    for (unsigned char byte : buffer) {
        char_array_3[i++] = byte;
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for (i = 0; i < 4; i++) {
                encoded += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        for (j = 0; j < i + 1; j++) {
            encoded += base64_chars[char_array_4[j]];
        }
        while (i++ < 3) {
            encoded += '=';
        }
    }

    return encoded;
}

int main() {
    // Defina a porta
    const int port = 55000;

    // Crie um socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Erro ao criar socket: " << strerror(errno) << std::endl;
        return 1;
    }

    // Bind do socket à porta
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Erro ao fazer bind: " << strerror(errno) << std::endl;
        return 1;
    }

    // Listen no socket
    if (listen(sockfd, 5) < 0) {
        std::cerr << "Erro ao listen: " << strerror(errno) << std::endl;
        return 1;
    }

    while (true) {
        // Aceite uma nova conexão
        int clientfd = accept(sockfd, nullptr, nullptr);

        if (clientfd < 0) {
            std::cerr << "Erro ao aceitar conexão: " << strerror(errno) << std::endl;
            continue;
        }

        std::cout << "Aguardando Requisições na porta: ->>  " << port << std::endl;

        // Receba a requisição
        char request[1024];
        int bytes_received = recv(clientfd, request, sizeof(request), 0);
        if (bytes_received < 0) {
            std::cerr << "Erro ao receber requisição: " << strerror(errno) << std::endl;
            close(clientfd);
            continue;
        }

        std::cout << "Conexão recedida com sucesso ->>  " << request << "\n\n" << std::endl;

        // Crie a resposta HTML com o cabeçalho Content-Type
        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/html\r\n\r\n";
        response += "<!DOCTYPE html>";
        response += "<html><head><title>Resposta do Servidor</title></head>";
        response += "<body>";
        response += "<h1>Aqui está a sua resposta!</h1>";
        response += "<p>Você enviou a seguinte requisição:</p>";
        response += "<pre>";
        response += request;
        response += "</pre>";

        // Adicione a imagem ao corpo da resposta
        std::string imagePath = "200.jpg"; // Substitua pelo caminho real da sua imagem
        std::string imageData = readFileAndEncodeBase64(imagePath);
        if (!imageData.empty()) {
            response += "<img src=\"data:image/jpeg;base64," + imageData + "\" alt=\"Minha Imagem\">";
        } else {
            response += "<p>Imagem não encontrada.</p>";
        }

        response += "</body></html>";

        // Envie a resposta
        int bytes_sent = send(clientfd, response.c_str(), response.length(), 0);
        if (bytes_sent < 0) {
            std::cerr << "Erro ao enviar resposta: " << strerror(errno) << std::endl;
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
