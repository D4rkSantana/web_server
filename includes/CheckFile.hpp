/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckFile.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:04:35 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/03 18:15:00 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CheckFile_HPP
#define CheckFile_HPP


#include "./library.hpp"

#include <sstream>
#include <string>




class CheckFile{
    private:
        bool _status;
        std::set<std::string> _getValidFirstWords(void);
        int _isFirstWordInSet(const std::string& text, const std::set<std::string>& wordSet);
    public:
        CheckFile(std::string path);
        ~CheckFile(void);

};

#endif