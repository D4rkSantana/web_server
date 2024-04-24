#include <iostream>
#include <map>
#include <vector>
#include <string>

typedef std::map<std::string, std::vector<std::string> > params;

typedef struct {
    params *server;
    params **locations;
} conf_servers;

void printValue(const conf_servers* _cservers, const std::string& key) {
    std::cout << "Value for key '" << key << "' in first location params: ";
    std::cout << (*_cservers->locations[0])[key][0] << std::endl;
}

int main() {
    // Exemplo de inicialização de conf_servers
    conf_servers* _cservers = new conf_servers();

    // Exemplo de dados para server e locations
    params* serverParams = new params;
    (*serverParams)["listen"].push_back("3008");
    (*serverParams)["index"].push_back("hello.html");
    // Adicione outros parâmetros conforme necessário...

    params** locationsParams = new params*[2];
    locationsParams[0] = new params;
    (*locationsParams[0])["location1_param1"].push_back("value1");
    // Adicione outros parâmetros de location conforme necessário...
    locationsParams[1] = NULL; // Sinalizando o final do vetor

    // Atribuindo os dados ao conf_servers
    _cservers->server = serverParams;
    _cservers->locations = locationsParams;

    // Chamando a função para imprimir o valor para uma chave específica
    printValue(_cservers, "location1_param1");

    // Lembre-se de liberar a memória alocada
    delete _cservers->server;
    delete _cservers->locations[0];
    delete[] _cservers->locations;
    delete _cservers;

    return 0;
}
