/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 21:29:29 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/13 22:23:23 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

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

    int         statusCode;

};


# endif
