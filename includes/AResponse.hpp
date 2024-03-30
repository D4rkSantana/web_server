/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AResponse.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:49:07 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/25 13:53:47 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ARESPONSE_HPP
#define ARESPONSE_HPP


#include "ErrorPage.hpp"
#include "Libs.hpp"
#include "Request.hpp"


class AHttpResponse {
    protected:
    HttpRequest  _req;
    responseData _res;
    ErrorPage    _errorPage;

    public:
    AHttpResponse(void);
    AHttpResponse(HttpRequest request);
    virtual ~AHttpResponse(void);

    virtual responseData handleMethod(void) = 0;
};


#endif