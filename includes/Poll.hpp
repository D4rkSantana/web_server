/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:53:32 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/25 16:18:20 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once


#include "Libs.hpp"

class Poll {
    private:
    std::vector<int>           _listeningSockets;
    std::vector<struct pollfd> _pollFds;
    std::vector<int>           _fdToClose;

    public:
    Poll(void);
    ~Poll(void);

    void init(int socketFd);
    void addPoll(int socketFd, short events);
    int  execute(void);
    bool isReadable(size_t i);
    bool isListeningSocketMatch(size_t i);
    void addFdToClose(int fd);
    void removeMarkedElements(void);
    void closePoll(void);

    void removeListeningSocket(int socketFd);
    void removePollFd(int socketFd);

    size_t getSize(void) const;
    int    getListeningSocket(size_t i) const;
    int    getPollFd(size_t i) const;
};
