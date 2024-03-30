/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteMethod.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:49:48 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/21 11:49:49 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#include "AResponse.hpp"
#include "Constants.hpp"
#include "utils.hpp"

class DeleteMethod : public AHttpResponse {
    public:
    DeleteMethod(void);
    DeleteMethod(HttpRequest request);
    ~DeleteMethod(void);

    responseData handleMethod(void);
};
