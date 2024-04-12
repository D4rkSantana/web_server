/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:29:55 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/12 16:45:58 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Poll_HPP
#define Poll_HPP

#include "Libs.hpp"

class Poll {
    private:
    std::vector<int>           _sockets;
    std::vector<struct pollfd> _pollFds;
    //std::vector<int>           _fdToClose;

    public:
    Poll(void);
    ~Poll(void);

    void init(int fd);
    int execute(void);
    bool isReadable(size_t i);
    bool isListeningSocketMatch(size_t i);
 
    
    /*
    bool isListeningSocketMatch(size_t i);
    void addFdToClose(int fd);
    void removeMarkedElements(void);
    void closePoll(void);

    void removeListeningSocket(int socketFd);
    void removePollFd(int socketFd);

    size_t getSize(void) const;
    int    getListeningSocket(size_t i) const;
    int    getPollFd(size_t i) const;

    */
    
};

#endif
