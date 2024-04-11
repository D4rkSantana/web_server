#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> separateServerBlocks(const std::string& config) {
    std::vector<std::string> blocks;
    std::string::size_type pos = 0;
    
    while ((pos = config.find("server {", pos)) != std::string::npos) {
        // Encontra o início do bloco
        std::string::size_type blockStart = pos;
        
        // Encontra o fim do bloco
        std::string::size_type blockEnd = config.find("}", blockStart);
        if (blockEnd == std::string::npos) {
            break; // Se não houver fechamento de bloco, termina
        }
        blockEnd = config.find("\n}", blockEnd); // Avança até a próxima linha após }
        if (blockEnd == std::string::npos) {
            break; // Se não houver fechamento de bloco, termina
        }
        blockEnd += 2; // Avança até o final do bloco

        // Adiciona o bloco encontrado ao vetor
        blocks.push_back(config.substr(blockStart, blockEnd - blockStart));

        // Move a posição de busca para após o bloco encontrado
        pos = blockEnd;
    }

    return blocks;
}

int main() {
    std::string config = "\
server {\n\
    listen 3007;\n\
    server_name jefernan.42.fr pmitsuko.42.fr localhost;\n\
    index hello.html;\n\
    root examples;\n\
    client_max_body_size 1024;\n\
    autoindex on;\n\
    error_page 404 notfound.html;\n\
\n\
    location /images {\n\
        limit_except GET POST;\n\
        autoindex off;\n\
        error_page 404 nocake.html;\n\
    }\n\
\n\
    location /pdfs {\n\
        limit_except GET;\n\
        index webserv.pdf;\n\
        autoindex off;\n\
    }\n\
\n\
    location /session {\n\
        index testcookie.html;\n\
        autoindex off;\n\
    }\n\
}\n\
\n\
server {\n\
    listen 3008;\n\
    index hello.html;\n\
    root examples;\n\
    client_max_body_size 1024;\n\
    error_page 404 notfound.html;\n\
\n\
    location /images {\n\
        limit_except GET;\n\
        autoindex on;\n\
        error_page 404 nocake.html;\n\
    }\n\
\n\
    location /pdfs {\n\
        index webserv.pdf;\n\
        autoindex off;\n\
    }\n\
\n\
    location /redirect {\n\
        limit_except GET POST;\n\
        redirect 302 https://www.42sp.org.br/;\n\
        autoindex off;\n\
        error_page 404 nocake.html;\n\
    }\n\
}\n\
";

    std::vector<std::string> blocks = separateServerBlocks(config);

    for (size_t i = 0; i < blocks.size(); ++i) {
        std::cout << "Block " << i + 1 << ":\n" << blocks[i] << std::endl << std::endl;
    }

    return 0;
}
