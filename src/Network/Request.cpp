#include <iostream>
#include "Request.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

void net::Request::execute(net::IClient &client, std::string data)
{
    client.send(data);
}
