/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:49:27 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/21 11:49:28 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#include "Libs.hpp"

class Constants {
    private:
    static const std::map<std::string, std::string> _mimeTypes;
    static const std::map<std::string, std::string> _statusCodes;
    static const std::set<std::string>              _cgiSupported;
    static std::map<std::string, std::string>       setMimeTypes();
    static std::map<std::string, std::string>       setStatusCodes();
    static std::set<std::string>                    setCgiSupported();

    public:
    Constants();
    ~Constants();

    static std::string getMimeTypes(std::string extension);
    static std::string getStatusCodes(std::string status);
    static bool        isCgi(std::string extension);
};
