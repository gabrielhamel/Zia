/**
 * @file HttpRequest.cpp
 * @author Loïc Bontemps (loic1.bontemps@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-27
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <criterion/criterion.h>
#include "HttpRequest.hpp"
#include <iostream>

static const std::string BasicRequest = "GET / HTTP/1.1\r\n"
    "Host: localhost:8080\r\n"
    "User-Agent: Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:66.0) Gecko/20100101 Firefox/66.0\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: en-US,en;q=0.5\r\n"
    "Accept-Encoding: gzip, deflate\r\n"
    "Connection: keep-alive\r\n"
    "Upgrade-Insecure-Requests: 1\r\n\r\n";

Test(HttpRequest, verb_1)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.verb(), http::HTTP_GET);
}

Test(HttpRequest, verb_2)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.verb(http::HTTP_POST), true);
}

Test(HttpRequest, route_1)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.route(), "/");
}

Test(HttpRequest, route_2)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.route("/ft/master/"), true);
    cr_assert_eq(request.route("/ft//master/"), true);
    cr_assert_eq(request.route("oui/"), false);
}

Test(HttpRequest, queryParameterExist)
{
    HttpRequest request(BasicRequest);

    request.route("/ft/master?value=key&name=lolo");
    cr_assert_eq(request.queryParameterExist("value"), true);
    cr_assert_eq(request.queryParameterExist("name"), true);
    cr_assert_eq(request.queryParameterExist("Unknown"), false);
}

Test(HttpRequest, queryParameter_1)
{
    HttpRequest request(BasicRequest);
    request.route("/ft/master?value=key&name=lolo");
    cr_assert_eq(request.queryParameter("value"), "key");
    cr_assert_eq(request.queryParameter("name"), "lolo");
    cr_assert_eq(request.queryParameter(""), "");
}

Test(HttpRequest, queryParameter_2)
{
    HttpRequest request(BasicRequest);

    request.route("/ft/master?value=key&name=lolo");
    cr_assert_eq(request.queryParameter("Unknown", "localhost:8080"), true);
    cr_assert_eq(request.queryParameter("", "Unknown"), false);
    cr_assert_eq(request.queryParameter("Unknown", ""), false);
    cr_assert_eq(request.queryParameter("", ""), false);
    cr_assert_eq(request.queryParameterExist("Unknown"), true);
}

Test(HttpRequest, cookie)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.headerParameter("Cookie", "yummy_cookie=choco"), true);
    cr_assert_eq(request.cookie("yummy_cookie"), "choco");
}

Test(HttpRequest, protocol)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.protocol(), "HTTP/1.1");
}

Test(HttpRequest, headerParameterExist)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.headerParameterExist("Connection"), true);
    cr_assert_eq(request.headerParameterExist("Unknown Header Parameter"), false);
}

Test(HttpRequest, headerParameter_1)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.headerParameter("Connection"), "keep-alive");
    cr_assert_eq(request.headerParameter("Header Parameter unknown"), "");
}

Test(HttpRequest, headerParameter_2)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.headerParameter("Connection", "keep-alive"), true);
    cr_assert_eq(request.headerParameter("Unknown Header Parameter", ""), false);
}

Test(HttpRequest, body)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.body(), "");
}

Test(HttpRequest, bodyAppend)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.bodyAppend(""), false);
    cr_assert_eq(request.bodyAppend("Test\r\n"), true);
    cr_assert_eq(request.body(), "Test\r\n");
    cr_assert_eq(request.headerParameter("Content-Length"), "6");
}

Test(HttpRequest, serialize)
{
    HttpRequest request(BasicRequest);

    cr_assert_eq(request.serialize(), BasicRequest);
}
