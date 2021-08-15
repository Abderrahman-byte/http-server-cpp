#include <string>
#include <sys/socket.h>
#include <iostream>

#include "http_parser/parser.hpp"
#include "connection.hpp"
#include "handleRequest.hpp"

void handleRequest(Connection connection, IncomingMessage_t request) {
    url_t request_url;
    std::string response_str;
    std::string body;

    body += "<html>";
    body += "<head>";
    body += "<title>Abderrahmane</title>";
    // body += "<script src='/static/main.js' ></script>";
    // body += "<script src='/static/index.js' ></script>";
    body += "</head>";
    body += "<body>";
    body += "<h1>Abderrahmane</h1>";
    body += "</body>";
    body += "</html>";

    response_str += "HTTP/1.1 200 OK\r\n";
    response_str += "Content-Type: text/html\r\n";
    response_str += "Connection: keep-alive\r\n";
    response_str += "Keep-Alive: timeout=5\r\n";
    response_str += "Content-Length: " + std::to_string(body.length()) + "\r\n";
    response_str += "Server: Abderrahmane\r\n";
    response_str += "\r\n";
    response_str += body;

    parse_url(&request_url, request.original_url);

    // For testing
    // std::cout << "[*] Parsed url : " << request_url.path << std::endl;
    // int s = request_url.searchquery.size();
    // std::cout << "[*] Parsed query : " <<  s << std::endl;

    // for (int i = 0; i < s ; i ++) {
    //     std::cout << "\t- " << request_url.searchquery[i].name << " => " << request_url.searchquery[i].value  << std::endl; 
    // } 

    send(connection.socket, response_str.c_str(), response_str.length(), MSG_DONTWAIT);
}