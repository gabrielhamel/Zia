#include <iostream>
#include "Request.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

void net::Request::execute(net::IClient &client, std::string data)
{
    std::string text = "HTTP/1.1 400 Bad Request\r\nServer: nginx/1.12.1\r\n";
    text += "Date: Mon, 20 Jan 2020 15:53:24 GMT\r\nContent-Type: text/html\r\nContent-Length: 173\r\n";
    text += "Connection: close\r\n\r\n<html>\r\n<head><title>400 Bad Request</title></head>\r\n";
    text += "<body bgcolor=\"white\">\r\n<center><h1>400 Bad Request</h1></center>\r\n<hr><center>nginx/1.12.1</center>\r\n";
    text += "</body>\r\n</html>\r\n\r\n";
    // HttpRequest request(data);
    // HttpResponse response(text);
    // std::cout << response.serialize() << std::endl;
    client.send(data);
}
