#include <iostream>
#include <map>
#include <string>

// Definição da classe Carro
class Carro {
public:
    std::string marca;
    std::string modelo;

    // Construtor padrão
    Carro() = default;

    // Construtor
    Carro(std::string marca, std::string modelo) : marca(marca), modelo(modelo) {}

    // Operador < para ordenação
    bool operator<(const Carro& outro) const {
        return modelo < outro.modelo; // Ordena carros por modelo
    }
};

int main() {
    // Criando um std::map com a chave como int e valor como Carro
    std::map<int, Carro> carros;

    // Inserindo elementos no mapa
    carros[1] = Carro("Toyota", "Corolla");
    carros[2] = Carro("Honda", "Civic");
    carros[3] = Carro("Ford", "Mustang");

    // Acessando e exibindo um elemento do mapa
    std::cout << "Carro 1: " << carros[1].marca << " " << carros[1].modelo << std::endl;

    // Iterando sobre os elementos do mapa e exibindo
    std::cout << "\nLista de carros:\n";
    for (const auto& par : carros) {
        std::cout << "Chave: " << par.first << ", Marca: " << par.second.marca << ", Modelo: " << par.second.modelo << std::endl;
    }

    return 0;
}
