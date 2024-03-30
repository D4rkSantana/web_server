/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndex.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:49:14 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/25 14:53:36 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef AUTOINDEX_HPP
#define AUTOINDEX_HPP


#include "ErrorPage.hpp"
#include "Libs.hpp"

#include "Request.hpp"
#include "ResponseHandlers.hpp"
#include "utils.hpp"


class AutoIndex {
    public:
    AutoIndex(void);
    AutoIndex(HttpRequest request);
    ~AutoIndex(void);

    responseData autoIndex(std::string root, std::string path, std::string port);

    private:
    // void			setResponse(std::string statusCode, std::string content);
    responseData _responseData;
    HttpRequest  _request;
    ErrorPage    _errorPage;
};


#endif