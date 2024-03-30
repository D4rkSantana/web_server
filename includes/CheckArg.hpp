/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckArg.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:43:05 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/30 01:15:43 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CheckArg_HPP
#define CheckArg_HPP


#include "./library.hpp"

class CheckArg{
    private:
        bool _status;
        bool _checkArgc(int argc);
        bool _checkArgv(char *argv[]);

    public:
        CheckArg(int argc, char *argv[]);
        ~CheckArg(void);
        
        bool getStatus(void);

};

bool fileExists(char *path);

# endif