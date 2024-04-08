/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckArg.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:43:05 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/08 00:31:50 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CheckArg_HPP
#define CheckArg_HPP

#include "./library.hpp"

class CheckArg {
    private:
        CheckArg ();
        static bool _checkArgc(int argc);
        static bool _checkArgv(char *argv[]);

    public:
        static bool check(int argc, char *argv[]);
};

bool isLineEmpty(const std::string& text);
bool checkBraces(const std::string& text);
bool fileExists(char *path);

# endif