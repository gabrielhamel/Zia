/**
 * @file HttpResponse.cpp
 * @author Loïc Bontemps (loic1.bontemps@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-27
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <criterion/criterion.h>
#include <iostream>
#include "HttpResponse.hpp"

static const std::string BasicResponse = "HTTP/1.1 400 Bad Request\r\nServer: nginx/1.12.1\r\n"
    "Date: Mon, 20 Jan 2020 15:53:24 GMT\r\nContent-Type: text/html\r\nContent-Length: 175\r\n"
    "Connection: close\r\n\r\n<html>\r\n<head><title>400 Bad Request</title></head>\r\n"
    "<body bgcolor=\"white\">\r\n<center><h1>400 Bad Request</h1></center>\r\n<hr><center>nginx/1.12.1</center>\r\n"
    "</body>\r\n</html>\r\n\r\n";

Test(HttpResponse, status_code)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.statusCode(), 400);
}

Test(HttpResponse, status_message_1)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.statusMessage(), "Bad Request");
}

Test(HttpResponse, status_message_2)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.statusCode(200), true);
    cr_assert_eq(response.statusCode(), 200);
    cr_assert_eq(response.statusCode(-1), false);
    cr_assert_eq(response.statusMessage("OK"), true);
    cr_assert_eq(response.statusMessage(), "OK");
    cr_assert_eq(response.statusMessage(""), false);
}

Test(HttpResponse, setCookie)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.headerParameterExist("Set-Cookie"), false);
    cr_assert_eq(response.setCookie("yummy_cookie", "choco"), true);
    cr_assert_eq(response.setCookie("tasty_cookie", "strawberry"), true);
    cr_assert_eq(response.headerParameterExist("Set-Cookie"), true);
    cr_assert_eq(response.headerParameter("Set-Cookie"), "yummy_cookie=choco");
    cr_assert_eq(response.headerParameter("Set-Cookie", "tasty_cookie=strawberry"), true);
}

Test(HttpResponse, protocol)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.protocol(), "HTTP/1.1");
}

Test(HttpResponse, headerParameterExist)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.headerParameterExist("Content-Type"), true);
    cr_assert_eq(response.headerParameterExist("Unknown Header Parameter"), false);
}

Test(HttpResponse, headerParameter_1)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.headerParameter("Content-Type"), "text/html");
    cr_assert_eq(response.headerParameter("Header Parameter unknown"), "");
}

Test(HttpResponse, headerParameter_2)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.headerParameter("Date", "Mon, 20 Jan 2020 15:53:24 GMT"), true);
    cr_assert_eq(response.headerParameter("Unknown Header Parameter", ""), false);
}

Test(HttpResponse, body)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.body(), "<html>\r\n<head><title>400 Bad Request</title></head>\r\n"
    "<body bgcolor=\"white\">\r\n<center><h1>400 Bad Request</h1></center>\r\n<hr><center>nginx/1.12.1</center>\r\n"
    "</body>\r\n</html>\r\n\r\n");
}

Test(HttpResponse, bodyAppend)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.bodyAppend(""), true);
    cr_assert_eq(response.bodyAppend("Test\r\n"), true);
    cr_assert_eq(response.body(), "<html>\r\n<head><title>400 Bad Request</title></head>\r\n"
    "<body bgcolor=\"white\">\r\n<center><h1>400 Bad Request</h1></center>\r\n<hr><center>nginx/1.12.1</center>\r\n"
    "</body>\r\n</html>\r\n\r\nTest\r\n");
    cr_assert_eq(response.headerParameter("Content-Length"), "181");
}

Test(HttpResponse, serialize)
{
    HttpResponse response(BasicResponse);

    cr_assert_eq(response.serialize(), BasicResponse, "GOT: %s\nEXPECT: %s\n", response.serialize().c_str(), BasicResponse.c_str());
}

Test(HttpResponse, noProtocol)
{
    std::string text("400 Request\r\n\r\n");
    bool ok = false;
    try {
        HttpResponse response(text);
    }
    catch (const std::runtime_error &e) {
        cr_assert_eq(std::string(e.what()), "Error no protocol or no status code or no status msg or missing one of them");
        ok = true;
    }
    cr_assert_eq(ok, true);
}

Test(HttpResponse, invalidKeyValue)
{
    std::string text("HTTP/1.1 400 Bad Request\r\nissou\r\n\r\n");
    bool ok = false;
    try {
        HttpResponse response(text);
    }
    catch (const std::runtime_error &e) {
        cr_assert_eq(std::string(e.what()), "String not type of key: value");
        ok = true;
    }
    cr_assert_eq(ok, true);
}

Test(HttpResponse, invalidStatusCode)
{
    std::string text("HTTP/1.1 -42 Request\r\n\r\n");
    bool ok = false;
    try {
        HttpResponse response(text);
    }
    catch (const std::runtime_error &e) {
        cr_assert_eq(std::string(e.what()), "Status code less than 0");
        ok = true;
    }
    cr_assert_eq(ok, true);
}

Test(HttpResponse, invalidCookie)
{
    HttpResponse res;

    cr_assert_eq(res.setCookie("", ""), false);
}

Test(HttpResponse, cookieAlreadyExist)
{
    HttpResponse res;

    cr_assert_eq(res.setCookie("one", "two"), true);
    cr_assert_eq(res.setCookie("one", "two"), true);
}

Test(HttpResponse, cookieOptions)
{
    HttpResponse res;
    CookieOptions options;
    options.push_back(std::make_pair<std::string, std::string>("taste", "good"));

    cr_assert_eq(res.setCookie("one", "two", options), true);
}
