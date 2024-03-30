/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:53:26 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/29 22:08:56 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PARSE_HPP
#define PARSE_HPP


#include "Libs.hpp"
#include "utils.hpp"


typedef std::map<std::string, std::vector<std::string> > params;

typedef struct {
    params  *server;
    params **locations;
} conf_servers;

class Parser
{
    private:
        conf_servers*       _cservers;
        int                 _servers;
        std::vector<int>    _locs;
        bool                _verbose;
    public:
        Parser();
        Parser(const char* fileconf);
        ~Parser();

        void init(const char* fileconf, bool verbose = false);
        void setConfs(const char* fileconf);
        void allocateServers(conf_servers* server, int locs);
        void deallocateServers(conf_servers* server, int locs);
        void clearParams();
        void populateConfs(std::vector<std::vector<std::string> > servers, std::vector<std::vector<std::string> > locations);
        std::vector<std::string> getServerParam (int server, std::string param);
        std::vector<std::string> getLocationParam (int server, int location, std::string param);
        std::vector<int> getSizeServers ();
        int getServers( void ) const;
};

std::vector<std::string> splitTokens(const std::string str);
std::string removeExtraSpaces(const std::string& input);
params* setParams(const std::string str, params* vconfs);




#endif