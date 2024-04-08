#include <iostream>
#include <string>

struct headers_general_s {
  std::string cache-control;
  std::string connection;
  std::string date;
  std::string pragma;
  std::string trailer;
  std::string transfer-encoding;
  std::string upgrade;
  std::string via;
  std::string warning;
} headers_general_t;

struct headers_request_s {
  std::string accept;
  std::string accept-charset;
  std::string accept-encoding;
  std::string accept-language;
  std::string authorization;
  std::string expect;
  std::string from;
  std::string host;
  std::string if-match;
  std::string if-modified-since;
  std::string if-none-match;
  std::string if-range;
  std::string if-unmodified-since;
  std::string max-forwards;
  std::string proxy-authorization;
  std::string range;
  std::string referer;
  std::string te;
  std::string user-agent;
} headers_request_s;

class Request{
  private:
    std::string         _raw_request;//     mensagem crua
    bool                _requestIntegrity;//status da integridade
    std::string         _method;//          metodo utilizado ex: GET POST
    std::string         _uri;//             recurso desejado
    std::string         _http_version;//    versçao do HTTP
    headers_general_t   _headers_general;// struct com headers gerais
    headers_request_t   _headers_request;// struct com headers exclusivos de requisicao

    //verifica a integrigade da requisicao crua
    bool                _checkRequest(std::string request);
    //faz a leitura da requisicao e guarda nas variaveis
    bool                _readRequest(std::string request);

  public:
    bool                getIntegrity(void);
    headers_general_t   getHeadersGeneral(void);
    headers_request_t   getHeadersRequest(void);
};




/*
Geral:

std::string cache-control
std::string connection
std::string date
std::string pragma
std::string trailer
std::string transfer-encoding
std::string upgrade
std::string via
std::string warning

Requisição:

std::string accept
std::string accept-charset
std::string accept-encoding
std::string accept-language
std::string authorization
std::string expect
std::string from
std::string host
std::string if-match
std::string if-modified-Since
std::string if-none-Match
std::string if-range
std::string if-Unmodified-Since
std::string max-forwards
std::string proxy-authorization
std::string range
std::string referer
std::string te
std::string user-agent
*/