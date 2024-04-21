/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConf.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:23:58 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/21 20:50:07 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConf.hpp"

std::vector<std::string> separateServerBlocks(const std::string &config)
{
    std::vector<std::string> blocks;
    std::string::size_type pos = 0;

    while ((pos = config.find("server {", pos)) != std::string::npos)
    {
        // Encontra o início do bloco
        std::string::size_type blockStart = pos;

        // Encontra o fim do bloco
        std::string::size_type blockEnd = config.find("}", blockStart);
        if (blockEnd == std::string::npos)
        {
            break; // Se não houver fechamento de bloco, termina
        }
        blockEnd = config.find("\n}", blockEnd); // Avança até a próxima linha após }
        if (blockEnd == std::string::npos)
        {
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

std::string extractServerParams(const std::string &serverBlock)
{
    std::istringstream iss(serverBlock);
    std::string line;
    std::string serverParams;
    bool insideLocation = false;

    while (std::getline(iss, line))
    {
        if (line.find("location") != std::string::npos)
        {
            insideLocation = true;
            continue; // Ignoramos a linha que contém "location"
        }
        if (line.find("}") != std::string::npos)
        {
            insideLocation = false;
            continue; // Ignoramos a linha que contém "}"
        }
        if (insideLocation)
        {
            continue; // Ignoramos as linhas dentro de uma localização
        }
        if (line.find("server {") != std::string::npos)
        {
            continue; // Ignoramos a linha "server {"
        }
        serverParams += line + "\n";
    }
    return serverParams;
}

std::vector<std::string> extractLocations(const std::string &serverBlock)
{
    std::istringstream iss(serverBlock);
    std::string line;
    std::vector<std::string> locations;
    bool insideLocation = false;
    std::string currentLocation;

    while (std::getline(iss, line))
    {
        if (line.find("location") != std::string::npos)
        {
            insideLocation = true;
            currentLocation = line + "\n";
            continue; // Ignoramos a linha que contém "location"
        }
        if (line.find("}") != std::string::npos && insideLocation)
        {
            insideLocation = false;
            locations.push_back(currentLocation + line); // Adicionamos a localização ao vetor
            continue;                                    // Ignoramos a linha que contém "}"
        }
        if (insideLocation)
        {
            currentLocation += line + "\n"; // Adicionamos a linha à localização atual
        }
    }
    return locations;
}

std::string getFirstWord(const std::string &text, int position)
{
    std::istringstream iss(text); // Cria um stream de string a partir do texto
    std::string line;
    int nbrLine;

    // Itera sobre cada linha do texto
    nbrLine = 0;
    while (std::getline(iss, line))
    {
        std::istringstream lineStream(line); // Cria um stream de string a partir da linha
        std::string firstWord;

        if (nbrLine == position)
        {
            lineStream >> firstWord;
            return firstWord;
        }
        nbrLine++;
    }
    return "";
}

int countWordOccurrencesLine(const std::string &text, const std::string &word)
{
    std::istringstream iss(text); // Cria um stream de string a partir do texto
    std::string line;
    int count;

    // Itera sobre cada linha do texto
    count = 0;
    while (std::getline(iss, line))
    {
        std::istringstream lineStream(line); // Cria um stream de string a partir da linha
        std::string firstWord;

        lineStream >> firstWord;
        if (firstWord == word)
        {
            count++;
        }
    }
    return count;
}

std::string getParameterValue(const std::string &text, const std::string &parameter)
{
    // Encontra a posição do parâmetro no texto
    size_t pos = text.find(parameter);
    if (pos == std::string::npos)
    {
        // Se o parâmetro não for encontrado, retorna uma string vazia
        return "";
    }

    // Avança para o valor do parâmetro
    pos += parameter.length();

    // Ignora os espaços em branco
    while (pos < text.length() && text[pos] == ' ')
    {
        pos++;
    }

    // Encontra o fim do valor do parâmetro
    size_t end_pos = text.find("\n", pos);
    if (end_pos == std::string::npos)
    {
        // Se o fim do texto for alcançado, retorna o restante da string
        return text.substr(pos);
    }

    // Retorna a parte do texto contendo o valor do parâmetro
    return text.substr(pos, end_pos - pos);
}

bool isNumeric(const std::string &str)
{
    // Verifica cada caractere da string
    for (size_t i = 0; i < str.length(); ++i)
    {
        // Se o caractere não for um dígito, retorna falso
        if (!(str[i] >= '0' && str[i] <= '9'))
        {
            return false;
        }
    }
    // Se todos os caracteres forem dígitos, retorna verdadeiro
    return true;
}

bool verifyLineEmpty(const std::string &text)
{

	bool emptyLine = true;

	for (size_t i = 0; i < text.length(); i++)
	{
		if (!isspace(text[i]))
		{
			emptyLine = false;
			return emptyLine;
		}
	}
	return emptyLine;
}

std::vector<std::string> splitTokens(const std::string str)
{
	std::vector<std::string> vtokens;
	std::istringstream iss(str);
	std::string token;

	while (iss >> token)
	{
		if (token == "{" || token == "}")
			continue;
		vtokens.push_back(token);
	}
	return vtokens;
}

std::string rmSpaces(const std::string &input)
{
	std::string result;
	bool previousCharWasSpace = false;

	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] != ' ')
		{
			result += input[i];
			previousCharWasSpace = false;
		}
		else if (!previousCharWasSpace)
		{
			result += ' ';
			previousCharWasSpace = true;
		}
	}
	if (result[0] == ' ')
	{
		result.erase(0, 1);
	}
	if (!result.empty() && result[result.length() - 1] == ' ')
	{
		result.erase(result.length() - 1);
	}
	return result;
}

bool endBlock(const std::string &line)
{
	std::string::size_type pos = 0;
	bool onlyClosingBrace = true;
	int countBrace = 0;
	int countSpace = 0;

	while (pos < line.length() && line[pos] != '\n')
	{
		if (line[pos] != '}' && line[pos] != ' ')
		{
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

void allocateServers(conf_servers *stConfServer, int qtLocation)
{

	stConfServer->server = new dic;
	stConfServer->locations = new dic *[qtLocation];

	for (int i = 0; i < qtLocation; i++)
		stConfServer->locations[i] = new dic;
}

void deallocateServers(conf_servers *stConfServer, int qtLocation)
{
	if (stConfServer)
	{
		for (int i = 0; i < qtLocation; i++)
		{
			if (stConfServer->locations[i])
			{
				delete stConfServer->locations[i];
			}
		}
		if (stConfServer->locations)
		{
			delete[] stConfServer->locations;
		}
		delete stConfServer->server;
	}
}