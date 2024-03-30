/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AResponse.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:54:20 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/21 11:54:21 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "AResponse.hpp"

AHttpResponse::AHttpResponse(void) {}

AHttpResponse::AHttpResponse(HttpRequest request) : _req(request) {}

AHttpResponse::~AHttpResponse(void) {}
