/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPage.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:49:53 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/21 11:49:54 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "Libs.hpp"
#include "utils.hpp"

class ErrorPage {
    private:
    bool        _hasErrorPageConfig(std::vector<std::string> errorPage, int statusCode);
    std::string _getPath(std::string uri);

    public:
    ErrorPage(void);
    ~ErrorPage(void);

    responseData getErrorPageContent(std::vector<std::string> errorPage,
                                     int                      statusCode,
                                     std::string              uri,
                                     std::string              root);
    responseData getErrorPageStandard(int statusCode);
};
