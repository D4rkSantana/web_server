


#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "./Libs.hpp"


class Location {
    private:
        std::string  _indexPage;
        std::string  _uriExtension;
        Request  _req;
        responseData _responseData;
        // ErrorPage    _errorPage; ->virou função 
 
        void _setIndexPage(Parser &parser);
        void _getFileContent(void);
        void _getIndexContent(void);

    public:
        Location(void);
        //Location(HttpRequest request);
        ~Location(void);

        //void         setup(Parser &parser);
        //responseData getLocationContent(void);
};


#endif