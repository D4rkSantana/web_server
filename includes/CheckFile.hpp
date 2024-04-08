/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckFile.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:04:35 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/08 00:25:34 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CheckFile_HPP
#define CheckFile_HPP


#include "./library.hpp"

class CheckFile{
    private:
        CheckFile();
        std::set<std::string> _getValidFirstWords(void);
        int _isFirstWordInSet(const std::string& text, const std::set<std::string>& wordSet);
    public:
        bool check(std::string path);
};

std::vector<std::string> separateServerBlocks(const std::string& config);
#endif