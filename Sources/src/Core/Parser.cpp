#include <iostream>
#include "Parser.hpp"
#include "HttpRequest.hpp"

void zia::Parser::parse(std::shared_ptr<http::Client> client, std::string text)
{
    HttpRequest request = HttpRequest(text);
}
