/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:09:20 by lucasmar          #+#    #+#             */
/*   Updated: 2024/02/28 16:10:31 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"

Data::Data(void){}

Data::~Data(void){}

bool	Data::start(const char* pathConf){
	std::string                             line;
	bool                                    inServer = false;
	bool                                    inLocation = false;
	bool                                    blockEnd = false;
	std::string                             currentServerBlock;
	std::vector<std::vector<std::string> >  servers;
	std::vector<std::vector<std::string> >  locations;
	std::vector<std::string>                serverBlocks;
	std::vector<std::string>                locationBlocks;
	std::string                             currentLocationBlock;

	std::ifstream	conf(pathConf);
	if (!conf.is_open()) {
	  return (false);
	}
	conf.clear();
	conf.seekg(0, std::ios::beg);

	while (!conf.eof()) {
        std::getline(conf, line);

        if (verifyLineEmpty(line))
            continue;

        if (line.find("server ") != std::string::npos)
            inServer = true;

        if (line.find("location ") != std::string::npos)
            inLocation = true;

        if(inServer && !inLocation)
            currentServerBlock += line + "\n";

        if(inLocation)
            currentLocationBlock += line + "\n";

        if (endBlock(line)){
            if (inLocation){
                locationBlocks.push_back(currentLocationBlock);
                currentLocationBlock.clear();
                inLocation = false;
            } else if (inServer && !inLocation) {
                serverBlocks.push_back(currentServerBlock);
                currentServerBlock.clear();
                inServer = false;
                blockEnd = true;
            }
        }

        if (!inServer && !inLocation && blockEnd) {
            servers.push_back(serverBlocks);
            locations.push_back(locationBlocks);
            serverBlocks.clear();
            locationBlocks.clear();
            blockEnd = false;
        }
    }
    conf.close();

	std::cout << servers[1][0];


    //populateConfs(servers, locations);
	return(true);
}

bool	Data::verifyLineEmpty(const std::string& text) {

    bool emptyLine = true;

    for (size_t i = 0; i < text.length(); i++) {
        if (!isspace(text[i])) {
            emptyLine = false;
            return emptyLine;
        }
    }
    return emptyLine;
}

bool	Data::endBlock(const std::string& line) {
    std::string::size_type  pos = 0;
    bool                    onlyClosingBrace = true;
    int                     countBrace = 0;
    int                     countSpace = 0;

    while (pos < line.length() && line[pos] != '\n') {
        if (line[pos] != '}' && line[pos] != ' ') {
            onlyClosingBrace = false;
            break;
        }
        if (line[pos] == '}')
            countBrace++;
        if (line[pos] == ' ')
            countSpace++;
        ++pos;
    }
    if (countBrace != 1)
        onlyClosingBrace = false;
    if (countSpace == 0 && countBrace == 1)
        onlyClosingBrace = true;

    return onlyClosingBrace;
}
