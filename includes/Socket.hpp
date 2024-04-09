




#ifndef SOCKET_HPP
# define SOCKET_HPP





#include "library.hpp"


class Socket{
	private:
		std::map<int, Data>	_mapServer;
		std::vector<int>	_listSockets;
		fd_set	_readFds;
		fd_set	_writeFds;
		bool	_succeed;
		struct	sockaddr_in _sockaddr;


	public:
		Socket(void);
		~Socket(void);
		bool				start(std::map<int, Data>& mapServer);
		fd_set*				getReadFds(void);
		fd_set*				getWriteFds(void);
		std::vector<int>*	getListenSockets(void);
		bool				setListenSockets(int	socketFd);
		void				closed(void);
};


# endif