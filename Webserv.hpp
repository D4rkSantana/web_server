/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:54:01 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/09 00:52:29 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "./library.hpp"


class Webserv{

	private:
		std::map<int, Data>	_mapServer;
		Socket				_sockets;
		std::vector<int>	clientListSockets;
		std::vector<int>*	listSocketsPoint;
		struct timeval	timeout;
		fd_set			readFdsCopy;
		fd_set			writeFdsCopy;

	public:
		Webserv(void);
		~Webserv(void);
		bool	setDataServer(std::string pathConf);
		bool	start(void);
		void	stop(void);
};


#endif