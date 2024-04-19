/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:54:01 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/19 19:40:17 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "./Libs.hpp"

class Socket;

/*typedef std::map<std::string, std::vector<std::string> > dic;

typedef struct
{
	dic *server;
	dic **locations;
} conf_servers;*/

class WebServ
{

	private:
		size_t								_sizeServers;
		conf_servers						*_dataServers;
		std::vector<int>					_qtLocation;
		//Data								_data;
		int 								_bytesRead;
		Poll								_poll;
		std::map<std::string, std::string>	_statusCodes;
		std::vector<Socket *>				_sockets;

		bool								_newCliet(size_t i);
		void								_setStatusCode(void);

	public:
		WebServ(void);
		~WebServ(void);
		//Metodos
		bool						connect(void);
		int							start(void);
		void						stop(void);
		void						finish(void);
		void						populateConfs(std::vector<std::vector<std::string> > servers, std::vector<std::vector<std::string> > locations);
		//Search's
		int							searchServer(std::string port);
		int							searchLocation(size_t iS, std::string path);
		//Set's
		bool						setDataServer(const char *pathConf);
		void						setBytesRead(int nbr);
		dic							*setParams(const std::string str, dic *vconfs);
		//Get's
		int							getBytesRead(void);
		size_t						getQtSevers(void);
		std::vector<int>			getAllQtLocations(void);
		std::string					getStatusCode(std::string code);
		std::vector<std::string>	getServerValue(size_t index, std::string key);
		std::vector<std::string> 	getLocationValue(size_t iS, size_t iL, std::string key);
};

# endif
