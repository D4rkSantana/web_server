/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:58:34 by lucasmar          #+#    #+#             */
/*   Updated: 2024/02/26 22:24:05 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef DATA_HPP
#define DATA_HPP

#include "./Libs.hpp"


typedef std::map<std::string, std::vector<std::string> > dic;

typedef struct
{
	dic *server;
	dic **locations;
} conf_servers;

class Data {

	private:
		size_t					_sizeServers;
		conf_servers			*_dataServers;
		std::vector<int>		_qtLocation;
		//std::vector<Socket *>	_sockets;

	public:
		Data(void);
		~Data(void);
		bool start(const char *pathConf);
		bool endBlock(const std::string &text);
		bool verifyLineEmpty(const std::string &text);
		void populateConfs(std::vector<std::vector<std::string> > servers,
		std::vector<std::vector<std::string> > locations);
		void allocateServers(conf_servers *stConfServer, int qtLocation);
		dic *setParams(const std::string str, dic *vconfs);
		std::string rmSpaces(const std::string &input);
		std::vector<std::string> splitTokens(const std::string str);
		void deallocateServers(conf_servers *stConfServer, int qtLocation);
		void clearParams();
		
		int	searchServer(std::string port);
	
		//getters
		size_t getQtSevers(void);
		std::vector<int> getAllQtLocations(void);//verificar depois

		std::vector<std::string> getServerValue(size_t iS, std::string key);
		std::vector<std::string> getLocationValue(size_t iS, size_t iL, std::string key);
};

# endif
