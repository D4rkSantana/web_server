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

	//excluir print aqui
	std::cout << servers[1][0];


    populateConfs(servers, locations);
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

void	Data::populateConfs(
	std::vector<std::vector<std::string> > servers,
	std::vector<std::vector<std::string> > locations){

	_sizeServers = servers.size();
	_dataServers = new conf_servers[_sizeServers];


	for (size_t i = 0; i < _sizeServers; i++) {
		allocateServers(&_dataServers[i], locations[i].size());
		_dataServers[i].server = setParams(servers[i][0], _dataServers[i].server);
		for (size_t j = 0; j < locations[i].size(); j++) {
		    _dataServers[i].locations[j] =
				setParams(locations[i][j], _dataServers[i].locations[j]);
		}
		_qtLocation.push_back(locations[i].size());
	}

	//excluir print aqui
	std::cout << _dataServers[0]->server[0].key = "listen" << std::endl;


}

void	Data::allocateServers(conf_servers* stConfServer, int qtLocation) {

	stConfServer->server = new dic;
	stConfServer->locations = new dic*[qtLocation];

	for (int i = 0; i < qtLocation; i++)
		stConfServer->locations[i] = new dic;
}

dic* Data::setParams(const std::string str, dic* vconfs) {
	std::vector<std::string>    tokens;
	std::string                 tmp_str = str;
	std::string                 token;

	size_t pos = str.find('\n');
	while (pos != std::string::npos) {
		token = tmp_str.substr(0, pos);
		tokens.push_back(rmSpaces(token));
		tmp_str = tmp_str.substr(pos + 1);
		pos = tmp_str.find('\n');
	}
	for (size_t i = 0; i < tokens.size(); i++) {
		pos = tokens[i].find(' ');
		if (pos != std::string::npos) {
			std::string key = tokens[i].substr(0, pos);
			std::vector<std::string> value = splitTokens(tokens[i].substr(pos + 1));
			if (key != "server")
				(*vconfs)[key] = value;
		}
	}
	return vconfs;
}

std::string	Data::rmSpaces(const std::string& input) {
	std::string result;
	bool previousCharWasSpace = false;

	for (size_t i = 0; i < input.length(); i++) {
	if (input[i] != ' ') {
		result += input[i];
		previousCharWasSpace = false;
	} else if (!previousCharWasSpace) {
		result += ' ';
		previousCharWasSpace = true;
	}
	}
	if (result[0] == ' ') {
		result.erase(0, 1);
	}
	if (!result.empty() && result[result.length() - 1] == ' ') {
		result.erase(result.length() - 1);
	}
	return result;
}

std::vector<std::string> Data::splitTokens(const std::string str) {
	std::vector<std::string>	vtokens;
	std::istringstream			iss(str);
	std::string					token;

	while (iss >> token) {
		if (token == "{" || token == "}")
			continue;
		vtokens.push_back(token);
	}
	return vtokens;
}

void Data::deallocateServers(conf_servers* stConfServer, int qtLocation) {
    if (stConfServer) {
        for (int i = 0; i < qtLocation; i++) {
            if (stConfServer->locations[i]) {
                delete stConfServer->locations[i];
            }
        }
        if (stConfServer->locations) {
            delete[] stConfServer->locations;
        }
        delete stConfServer->server;
    }
}

void	Data::clearParams() {
    for (size_t i = 0; i < _sizeServers; i++) {
        deallocateServers(&_dataServers[i], _qtLocation[i]);
    }
    delete [] _dataServers;
}
