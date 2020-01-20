#include <iostream>
#include "Request.hpp"
#include "HttpRequest.hpp"

void net::Request::execute(net::IClient &client, std::string data)
{
    //HttpRequest request = HttpRequest(text);
    std::cout << data;
    client.send(data);
}
