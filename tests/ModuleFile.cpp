/**
 * @file ModuleFile.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2020-02-29
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <boost/dll.hpp>
#include <iostream>
#include <ModuleApi.hpp>
#include "Redirector.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

#ifndef _WIN32
    static const std::string path("build/lib/libfile.so");
#else
    static const std::string path("build\\bin\\file.dll");
#endif

static const std::string BasicRequest =
    "GET /index.html HTTP/1.1\r\n"
    "Host: localhost:8080\r\n"
    "Connection: keep-alive\r\n\r\n";

static std::unique_ptr<http::IRequest> request = std::make_unique<HttpRequest>(BasicRequest);
static boost::dll::shared_library library(path);

#ifndef _WIN32
    const std::string www("example/www");
#else
    const std::string www("example\\www");
#endif

static module::Api *mod = nullptr;

static std::string nullBuffer;

static void moduleCreate(void)
{
    mod = boost::dll::import_alias<module::Api *()>(library, "create_module")();
}

static void moduleDestroy(void)
{
    delete mod;
    mod = nullptr;
}

class FakeClient : public net::IClient
{
    bool send(const std::string &data) { return true; }
    std::size_t getId() const noexcept { return 0; }
};

std::unique_ptr<net::IClient> client = std::make_unique<FakeClient>();
std::unique_ptr<http::IResponse> response = std::make_unique<HttpResponse>();

TestSuite(ModuleFile);

Test(ModuleFile, hasFactory)
{
    cr_assert_eq(library.has("create_module"), true);
}

Test(ModuleFile, namse, .init = moduleCreate, .fini = moduleDestroy)
{
    cr_assert_eq(mod->name(), "file");
}

Test(ModuleFile, setConfiguration, .init = moduleCreate, .fini = moduleDestroy)
{
    std::unordered_map<std::string, std::string> configs;
    configs.emplace("root", www);

    cr_assert_eq(mod->setConfigurations(configs), true);
}

Test(ModuleFile, unknownRoot, .init = moduleCreate, .fini = moduleDestroy)
{
    Redirector redirect(std::cerr);
    std::unordered_map<std::string, std::string> configs;

    cr_assert_eq(mod->setConfigurations(configs), false);
    cr_assert_eq(redirect.getContent(), "Missing root folder\n");
}

Test(ModuleFile, uselessFunctions, .init = moduleCreate, .fini = moduleDestroy)
{
    cr_expect_eq(mod->newConnection(*client), true);
    cr_expect_eq(mod->disconnection(*client), true);
    cr_expect_eq(mod->afterReceive(*client, nullBuffer), true);
    cr_expect_eq(mod->afterUnpacked(*client, *request), true);
    cr_expect_eq(mod->beforePacked(*client, *response), true);
    cr_expect_eq(mod->beforeSend(*client, nullBuffer), true);
}

Test(ModuleFile, basicExecution, .init = moduleCreate, .fini = moduleDestroy)
{
    std::unordered_map<std::string, std::string> configs;
    configs.emplace("root", www);
    mod->setConfigurations(configs);
    std::unique_ptr<http::IResponse> res = std::make_unique<HttpResponse>();

    cr_assert_eq(mod->execute(*client, *request, *res), true);
    cr_assert_eq(res->statusCode(), 200);
    cr_assert_eq(res->statusMessage(), "OK");
    cr_assert_eq(res->headerParameter("Content-Length"), "15");
    cr_assert_eq(res->body(), "<h1>SALUT</h1>\n");
}

Test(ModuleFile, notFound, .init = moduleCreate, .fini = moduleDestroy)
{
    std::unordered_map<std::string, std::string> configs;
    configs.emplace("root", www);
    mod->setConfigurations(configs);
    static const std::string errorRequest =
        "GET /issou.html HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n\r\n";
    std::unique_ptr<http::IRequest> req = std::make_unique<HttpRequest>(errorRequest);
    std::unique_ptr<http::IResponse> res = std::make_unique<HttpResponse>();

    cr_assert_eq(mod->execute(*client, *req, *res), true);
    cr_assert_eq(res->statusCode(), 404);
    cr_assert_eq(res->statusMessage(), "Not found");
}

Test(ModuleFile, defaultMimetype, .init = moduleCreate, .fini = moduleDestroy)
{
    std::unordered_map<std::string, std::string> configs;
    configs.emplace("root", www);
    mod->setConfigurations(configs);
    static const std::string errorRequest =
        "GET /info.txt HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n\r\n";
    std::unique_ptr<http::IRequest> req = std::make_unique<HttpRequest>(errorRequest);
    std::unique_ptr<http::IResponse> res = std::make_unique<HttpResponse>();

    cr_assert_eq(mod->execute(*client, *req, *res), true);
    cr_assert_eq(res->statusCode(), 200);
    cr_assert_eq(res->statusMessage(), "OK");
    cr_assert_eq(res->headerParameter("Content-Type"), "application/octet-stream");
}

Test(ModuleFile, noExtension, .init = moduleCreate, .fini = moduleDestroy)
{
    std::unordered_map<std::string, std::string> configs;
    configs.emplace("root", www);
    mod->setConfigurations(configs);
    static const std::string errorRequest =
        "GET /noextension HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n\r\n";
    std::unique_ptr<http::IRequest> req = std::make_unique<HttpRequest>(errorRequest);
    std::unique_ptr<http::IResponse> res = std::make_unique<HttpResponse>();

    cr_assert_eq(mod->execute(*client, *req, *res), true);
    cr_assert_eq(res->statusCode(), 200);
    cr_assert_eq(res->statusMessage(), "OK");
    cr_assert_eq(res->headerParameter("Content-Type"), "application/octet-stream");
}

Test(ModuleFile, indexRedir, .init = moduleCreate, .fini = moduleDestroy)
{
    std::unordered_map<std::string, std::string> configs;
    configs.emplace("root", www);
    mod->setConfigurations(configs);
    static const std::string errorRequest =
        "GET / HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n\r\n";
    std::unique_ptr<http::IRequest> req = std::make_unique<HttpRequest>(errorRequest);
    std::unique_ptr<http::IResponse> res = std::make_unique<HttpResponse>();

    cr_assert_eq(mod->execute(*client, *req, *res), true);
    cr_assert_eq(res->statusCode(), 200);
    cr_assert_eq(res->statusMessage(), "OK");
}

Test(ModuleFile, noIndex, .init = moduleCreate, .fini = moduleDestroy)
{
    std::unordered_map<std::string, std::string> configs;
    configs.emplace("root", www);
    mod->setConfigurations(configs);
    static const std::string errorRequest =
        "GET /../ HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n\r\n";
    std::unique_ptr<http::IRequest> req = std::make_unique<HttpRequest>(errorRequest);
    std::unique_ptr<http::IResponse> res = std::make_unique<HttpResponse>();

    cr_assert_eq(mod->execute(*client, *req, *res), true);
    cr_assert_eq(res->statusCode(), 404);
    cr_assert_eq(res->statusMessage(), "Not found");
}
