/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:56:32 by lucasmar          #+#    #+#             */
/*   Updated: 2024/03/01 16:58:02 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Libs.hpp"

class Socket{
	private:
		std::map<int, Data> _mapServer;
		std::vector<int> _listenSockets;
		fd_set _readFds;
		fd_set _writeFds;
		bool _succeed;
		sockaddr_in _sockaddr;


	public:
		Socket(void);
		~Socket(void);
		bool				start(std::map<int, Data>& mapServer);
		fd_set				getReadFds(void);
		fd_set				getWriteFds(void);
		std::vector<int>&	getListenSockets(void);
		void				setListenSockets(int	socketFd);
		void				closed(void);
};
