/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:54:01 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/13 21:30:26 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "./Libs.hpp"

class Socket;

class WebServ
{

	private:
		Data								_data;
		int 								_bytesRead;
		Poll								_poll;
		std::map<std::string, std::string>	_statusCodes;
		std::vector<Socket *>				_sockets;

		bool	_newCliet(size_t i);
		void	_setStatusCode(void);

	public:
		WebServ(void);
		~WebServ(void);
		bool						setDataServer(const char *pathConf);
		bool						connect(void);
		int							start(void);
		void						stop(void);
		void						finish(void);
		size_t						getQtSevers(void);
		std::string					getStatusCode(std::string code);
		std::vector<std::string>	getServerValue(size_t index, std::string key);

		int getBytesRead(void);
		void setBytesRead(int nbr);
	
};

# endif
