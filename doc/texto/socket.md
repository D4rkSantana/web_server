#  O que é um socket ?

Um socket é um ponto de comunicação bidirecional que permite a troca de dados entre processos em uma rede, seja em uma mesma máquina ou entre diferentes máquinas. Ele é um dos principais conceitos na programação de redes e fornece uma interface abstrata para a comunicação entre processos.

Em sistemas baseados em Unix, incluindo Linux e macOS, os sockets são implementados como arquivos especiais que representam pontos de extremidade de uma conexão de rede. Existem vários tipos de sockets, sendo os mais comuns:

1. **Socket de fluxo (Stream Socket):** Também conhecido como TCP (Transmission Control Protocol) socket, fornece uma conexão confiável, orientada a fluxo e bidirecional entre os processos. Os dados enviados por um lado do socket são garantidos para chegar ao outro lado na mesma ordem e sem erros.

2. **Socket de datagrama (Datagram Socket):** Também conhecido como UDP (User Datagram Protocol) socket, fornece uma comunicação não confiável, orientada a datagrama e bidirecional entre os processos. Os dados enviados por um lado do socket podem chegar ao outro lado fora de ordem, duplicados ou podem até mesmo serem perdidos.

Os sockets são amplamente utilizados em aplicativos de rede para comunicação entre computadores em uma rede. Eles são usados em protocolos de comunicação como HTTP, FTP, SMTP, SSH, entre outros. Os programadores podem criar e utilizar sockets em suas aplicações para enviar e receber dados pela rede.

Em resumo, um socket é um ponto de comunicação que permite que processos em uma rede se comuniquem entre si, seja para trocar dados, estabelecer conexões ou realizar outras operações de rede.


## Exemplo;

Para criar um socket em C++, você pode usar a API de soquete (socket API) fornecida pelo sistema operacional. A API de soquete é padronizada e oferece funcionalidades para criar, configurar, conectar e enviar/receber dados por meio de sockets. Aqui está um exemplo simples de como criar um socket em C++ usando a API de soquete para criar um servidor TCP:


## Analogia: 
 Imagine um sistema de correio. O socket seria como a caixa de correio, onde as cartas (dados) são enviadas e recebidas. O endereço da caixa de correio (endereço IP e porta) identifica para onde a carta deve ser enviada ou de onde ela veio.


```cpp
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
```

Neste exemplo:

- Usamos a função `socket()` para criar um novo socket.
- Especificamos o tipo de socket como `SOCK_STREAM` para indicar que este será um socket TCP.
- Configuramos o endereço do servidor para escutar em todas as interfaces de rede (`INADDR_ANY`) na porta especificada (`PORT`).
- Usamos a função `bind()` para associar o endereço e a porta ao socket.
- Fechamos o socket após a conclusão da configuração.

Este é um exemplo simples de criação de um socket servidor TCP em C++. Certifique-se de adicionar tratamento de erros adequado e lógica adicional conforme necessário para sua aplicação.