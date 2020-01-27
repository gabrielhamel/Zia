/**
 * @file HttpResponse.cpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-27
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <criterion/criterion.h>
#include "HttpResponse.hpp"

static const std::string BasicResponse = "HTTP/1.1 400 Bad Request\r\nServer: nginx/1.12.1\r\n"
    "Date: Mon, 20 Jan 2020 15:53:24 GMT\r\nContent-Type: text/html\r\nContent-Length: 173\r\n"
    "Connection: close\r\n\r\n<html>\r\n<head><title>400 Bad Request</title></head>\r\n"
    "<body bgcolor=\"white\">\r\n<center><h1>400 Bad Request</h1></center>\r\n<hr><center>nginx/1.12.1</center>\r\n"
    "</body>\r\n</html>\r\n\r\n";

Test(HttpRequest, status_code)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.statusCode(), 400);
}

Test(HttpRequest, status_message)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.statusMessage(), "Bad Request");
}
