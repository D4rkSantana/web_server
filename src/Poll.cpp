/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:29:35 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/11 21:37:51 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"

Poll::Poll(void) {}

Poll::~Poll(void)
{
    this->closePoll();
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
