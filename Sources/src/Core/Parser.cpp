#include <iostream>
#include "Parser.hpp"
#include "HttpRequest.hpp"

void http::Parser::parse(http::Client &client, std::string text)
{
    HttpRequest request = HttpRequest(text);
}
