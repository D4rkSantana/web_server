/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteMethod.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:54:42 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/25 13:31:33 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "DeleteMethod.hpp"

DeleteMethod::DeleteMethod(void) {}

DeleteMethod::DeleteMethod(HttpRequest request) : AHttpResponse(request) {}

DeleteMethod::~DeleteMethod(void) {}

responseData DeleteMethod::handleMethod(void)
{
    std::string resourcePath = getDir();

    resourcePath = resourcePath + "/" + this->_req.getRoot() + this->_req.getUri();
    Logs::printLog(Logs::WARNING, 2,  "resourcePath: " + resourcePath);
    

    std::ifstream file(resourcePath.c_str());

    if (file.is_open()) {
        file.close();
        if (std::remove(resourcePath.c_str()) == 0) {
            this->_res = setResponseData(NO_CONTENT, "", "", 0);
            Logs::printLog(Logs::INFO, 3, "Resource deleted sucessfully!");
        } else {
            this->_res = this->_errorPage.getErrorPageContent(this->_req.getErrorPageConfig(),
                                                              INTERNAL_SERVER_ERROR,
                                                              this->_req.getUri(),
                                                              this->_req.getRoot());
            Logs::printLog(Logs::INFO, 3, "Error deleting resource!");
        }
    } else {
        this->_res = this->_errorPage.getErrorPageContent(
            this->_req.getErrorPageConfig(), NOT_FOUND, this->_req.getUri(), this->_req.getRoot());
        Logs::printLog(Logs::INFO, 3, "Resource not foud!");
    }
    return (this->_res);
}
