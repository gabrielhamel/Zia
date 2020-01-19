#include <iostream>
#include "Parser.hpp"
#include "HttpRequest.hpp"

void http::Parser::parse(net::IClient &client, std::string data)
{
    //HttpRequest request = HttpRequest(text);
    std::cout << data;
    client.send(data);
}
