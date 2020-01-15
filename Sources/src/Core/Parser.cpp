#include <iostream>
#include "Parser.hpp"
#include "HttpRequest.hpp"

void zia::Parser::parse(std::shared_ptr<zia::net::User> user, std::string text)
{
    HttpRequest request = HttpRequest(text);
}
