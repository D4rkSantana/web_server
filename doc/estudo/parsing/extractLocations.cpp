#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> extractLocations(const std::string& serverBlock) {
    std::istringstream iss(serverBlock);
    std::string line;
    std::vector<std::string> locations;
    bool insideLocation = false;
    std::string currentLocation;

    while (std::getline(iss, line)) {
        if (line.find("location") != std::string::npos) {
            insideLocation = true;
            currentLocation = line + "\n";
            continue; // Ignoramos a linha que contém "location"
        }
        if (line.find("}") != std::string::npos && insideLocation) {
            insideLocation = false;
            locations.push_back(currentLocation + line); // Adicionamos a localização ao vetor
            continue; // Ignoramos a linha que contém "}"
        }
        if (insideLocation) {
            currentLocation += line + "\n"; // Adicionamos a linha à localização atual
        }
    }

    return locations;
}

int main() {
    std::string serverBlock = R"(
        server {
            listen 3007;
            server_name new.42.fr pss.fr localhost;
            index hello.html;
            root guide;
            autoindex on;
            error_page 404 notfound.html;

            location /images {
                limit_except GET POST;
                autoindex off;
                error_page 404 nocake.html;
            }

            location /method {
                limit_except GET POST;
                error_page 404 notfound.html;
            }
            client_max_body_size 1024;
            location /pdfs {
                limit_except GET;
                index webserv.pdf;
            }
        }
    )";

    std::vector<std::string> locations = extractLocations(serverBlock);

    // Imprimir as localizações
    for (size_t i = 0; i < locations.size(); ++i) {
        std::cout << "Location " << i + 1 << ":\n" << locations[i] << std::endl << std::endl;
    }

    return 0;
}
