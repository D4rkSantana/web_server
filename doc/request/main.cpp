#include <algorithm>
#include <arpa/inet.h>

#include <ctime>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <cstdlib>

#include <fcntl.h>
#include <fstream>

#include <iomanip>
#include <iostream>

#include <map>

#include <netdb.h>
#include <netinet/in.h>

#include <set>
#include <stack>
#include <string>
#include <sstream>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <vector>

#include <unistd.h>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main() {
    try {
        // Inicializar o serviço IO
        boost::asio::io_context io_context;

        // Criar um objeto de aceitação para aceitar conexões
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "Servidor iniciado. Aguardando conexões..." << std::endl;

        while (true) {
            // Aguardar e aceitar uma conexão
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            // Construir a resposta HTTP (página HTML simples)
            std::string response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Connection: close\r\n"
                "\r\n"
                "<!DOCTYPE html>\n"
                "<html>\n"
                "<head><title>Exemplo de Servidor C++</title></head>\n"
                "<body>\n"
                "<h1>Olá, mundo!</h1>\n"
                "<p>Este é um exemplo de servidor C++ que envia uma página da web.</p>\n"
                "</body>\n"
                "</html>\n";

            // Enviar a resposta para o cliente
            boost::asio::write(socket, boost::asio::buffer(response));
        }
    } catch (std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
