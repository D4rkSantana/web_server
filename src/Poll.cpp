/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:29:35 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/12 18:22:56 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"

Poll::Poll(void) {}

Poll::~Poll(void)
{
   // this->closePoll();
}

void Poll::init(int fd)
{
    struct pollfd pollFd;

    pollFd.fd      = fd;
    pollFd.events  = POLLIN;
    pollFd.revents = 0;
    this->_sockets.push_back(fd);
    this->_pollFds.push_back(pollFd);
}


int Poll::execute(void){ 
    int result;
    result = poll(&this->_pollFds[0], this->_pollFds.size(), 0);
    
    return result; 
}


bool    Poll::isRead(size_t i) const{ 
    bool    result;
        
    result = this->_pollFds[i].revents & POLLIN;
    if(result)
        return (true);
    else
        return (false);
}

bool Poll::waitMatch(size_t i)
{
    bool result;

    result =  i < this->_sockets.size() && this->_pollFds[i].fd == this->_sockets[i];
    
    return (result);
}



int Poll::getPollFd(size_t i) const
{
    if (i < this->_pollFds.size()) {
        return this->_pollFds[i].fd;
    }
    return (-1);
}



size_t Poll::getSize(void) const{ 
    size_t result;

    result = this->_pollFds.size();
    return (result); 
}


