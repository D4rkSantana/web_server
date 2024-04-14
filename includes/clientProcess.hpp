



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



void        processClientData(int fd);
std::string getStatusCodes(std::string status);
std::string readClientData(int fd);
std::string mergeStrVector(std::vector<std::string> vec, std::string delimiter);

#endif
