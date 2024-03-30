/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:50:12 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/21 11:50:13 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "ErrorPage.hpp"
#include "Libs.hpp"
#include "Parser.hpp"
#include "Request.hpp"
#include "utils.hpp"

class Location {
    private:
    std::string  _indexPage;
    std::string  _uriExtension;
    HttpRequest  _req;
    responseData _responseData;
    ErrorPage    _errorPage;

    void _setIndexPage(Parser &parser);
    void _getFileContent(void);
    void _getIndexContent(void);

    public:
    Location(void);
    Location(HttpRequest request);
    ~Location(void);

    void         setup(Parser &parser);
    responseData getLocationContent(void);
};
