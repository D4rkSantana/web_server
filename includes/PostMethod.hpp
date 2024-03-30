/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostMethod.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:53:37 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/21 11:53:39 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "AResponse.hpp"

class PostMethod : public AHttpResponse {

    public:
    PostMethod();
    PostMethod(HttpRequest request);
    ~PostMethod();

    responseData    handleMethod();
    bool            verifyLimit();
    bool            handleMultipart();
    void            handleForm();
    void            print();
    void            saveFile(std::string &fileName, const std::string &value);
    void            parseMultipartFormData(size_t pos, size_t endPos);

    bool created;

    private:
    bool                               _file;
    size_t                                 _bodySize;
    std::map<std::string, std::string> _formData;
};
