/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 21:29:29 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/14 19:27:47 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "Libs.hpp"

class Request
{
    private:
    std::string                        _uri;//
    std::string                        _body;
    std::string                        _port;
    std::string                        _host;
    std::string                        _method;//
    std::string                        _boundary;
    std::string                        _httpVersion;//
    std::vector<std::string>			_allowMethods;//
    std::vector<std::string>           _paramQuery;

    public:
    
        Request();
        ~Request();
        int         statusCode;
        void        init();
        bool        requestHttp(std::string request);
        bool        _parseFirstLine(std::string &requestLine);
        void        _parseQuery(void);
        void        _parseHeaders(const std::string &request);
        void        _findHeaders(std::string key, std::string value);
        void        _getServerParam(void);
        void        _getMaxBody(void);
        std::string _catchPathURI(void);
        void        _setRoot(void);
        void        _setLimitExcept(void);
        void        _setErrorPage(void);
        void        _setAutoIndex(void);


};


# endif
