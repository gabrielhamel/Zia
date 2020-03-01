/**
 * @file ModuleProxy.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2020-03-01
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
#include "Configurations.hpp"

#ifndef _WIN32
    static const std::string path("build/lib/libproxy.so");
#else
    static const std::string path("build\\bin\\proxy.dll");
#endif

#ifndef _WIN32
    const std::string config("example/config.linux.yml");
#else
    const std::string config("example\\config.windows.yml");
#endif

static const std::string BasicRequest =
    "GET /proxy/index.html HTTP/1.1\r\n"
    "Host: localhost\r\n"
    "Connection: keep-alive\r\n\r\n";

static std::unique_ptr<http::IRequest> request = std::make_unique<HttpRequest>(BasicRequest);
static std::unique_ptr<http::IResponse> response = std::make_unique<HttpResponse>();

class FakeClient : public net::IClient
{
    bool send(const std::string &data) { return true; }
    std::size_t getId() const noexcept { return 0; }
};

static std::unique_ptr<net::IClient> client = std::make_unique<FakeClient>();

static boost::dll::shared_library library(path);
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

TestSuite(ModuleProxy);

Test(ModuleProxy, hasFactory)
{
    cr_assert_eq(library.has("create_module"), true);
}

Test(ModuleProxy, namse, .init = moduleCreate, .fini = moduleDestroy)
{
    cr_assert_eq(mod->name(), "proxy");
}

Test(ModuleProxy, uselessFunctions, .init = moduleCreate, .fini = moduleDestroy)
{
    cr_expect_eq(mod->newConnection(*client), true);
    cr_expect_eq(mod->disconnection(*client), true);
    cr_expect_eq(mod->afterReceive(*client, nullBuffer), true);
    cr_expect_eq(mod->afterUnpacked(*client, *request), true);
    cr_expect_eq(mod->beforePacked(*client, *response), true);
    cr_expect_eq(mod->beforeSend(*client, nullBuffer), true);
}

Test(ModuleProxy, configuration, .init = moduleCreate, .fini = moduleDestroy)
{
    core::Configurations configs(config);
    auto proxy = configs.getHostByDomain("localhost").getRouteByName("\\/proxy").getModule("proxy");
    mod->setConfigurations(proxy.getConfigs());
}

Test(ModuleProxy, exec, .init = moduleCreate, .fini = moduleDestroy)
{
    core::Configurations configs(config);
    auto proxy = configs.getHostByDomain("localhost").getRouteByName("\\/proxy").getModule("proxy");
    mod->setConfigurations(proxy.getConfigs());
    Redirector redirect(std::cerr);
    mod->execute(*client, *request, *response);
}
