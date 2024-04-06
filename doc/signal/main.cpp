#include <csignal>
#include <iostream>

// Variável de sinalização para indicar se o programa deve terminar
volatile sig_atomic_t terminar_programa = 0;

// Função de tratamento de sinal
void signal_handler(int signal) {
    std::cout << "Sinal recebido: " << signal << std::endl;
    // Configura a variável de sinalização para indicar que o programa deve terminar
    terminar_programa = 1;
}

class Pessoa {
    public:
        std::string nome;
        int idade;
        Pessoa(std::string nome, int idade) {
            this->nome = nome;
            this->idade = idade;
        }
        ~Pessoa() {
            std::cout << "Destrutor chamado para " << this->nome << std::endl;
        }
};


int main() {
    // Configurar o tratador de sinal
    std::signal(SIGINT, signal_handler); // Trata o sinal de interrupção (Ctrl+C)

    std::cout << "Pressione Ctrl+C para enviar um sinal SIGINT...\n";

    // Loop principal
    Pessoa a = Pessoa("João", 20);
    while (!terminar_programa) {
        // Lógica do programa aqui
    }

    std::cout << "Programa terminado.\n";

    return 0;
}
