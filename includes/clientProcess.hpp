



#ifndef clientProcess_HPP
#define clientProcess_HPP

#include "./Libs.hpp"


struct responseData {
    int         status;
    std::string content;
    std::string statusCode;
    std::string contentType;
    int         contentLength;
    std::string location;
};

responseData setResponseData(int         status,
                             std::string contentType,
                             std::string content,
                             int         contentLength,
                             std::string location);



std::string getStatusCodes(std::string status);


#endif