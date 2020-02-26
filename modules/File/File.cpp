/**
 * @file File.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief An basic module who say hello at each requests
 * @version 1.0
 * @date 2020-02-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <boost/dll/alias.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <regex>
#include <unordered_map>

#include "File.hpp"

static const std::unordered_map<std::string, std::string> mimetype = {
    {"html", "text/html"},
    {"css", "text/css"},
    {"js", "text/javascript"},
    {"gif", "image/gif"},
    {"png", "image/png"},
    {"jpeg", "image/jpeg"},
    {"jpg", "image/jpeg"},
    {"bmp", "image/bmp"},
    {"webp", "image/webp"},
    {"mp4", "audio/mpeg"},
    {"mp3", "audio/mpeg"},
    {"ogg", "audio/ogg"}
};

module::File::File()
{

}

module::File::~File()
{

}

std::string module::File::name() const noexcept
{
    return std::move(std::string("file"));
}

bool module::File::newConnection(const net::IClient &client) noexcept
{
    return true;
}

bool module::File::disconnection(const net::IClient &client) noexcept
{
    return true;
}

bool module::File::setConfigurations(Configs configs) noexcept
{
    const auto &root = configs.find("root");
    if (root == configs.end()) {
        std::cerr << "Missing root folder" << std::endl;
        return false;
    }
    m_rootFolder = root->second;
    return true;
}

bool module::File::afterReceive(const net::IClient &client, std::string &buffer) noexcept
{
    return true;
}

bool module::File::afterUnpacked(const net::IClient &client, http::IRequest &request) noexcept
{
    return true;
}

bool module::File::responseError(int status, std::string message, http::IResponse &response) const
{
    response.statusCode(status);
    response.statusMessage(message);
    response.body( "<html>\r\n"                                            \
                    "<head><title>" + std::string(std::to_string(status) + std::string(" ") + message) + "</title></head>\r\n"       \
                    "<body>\r\n"                                            \
                    "<center><h1>" + std::string(std::to_string(status) + std::string(" ") + message) + "</h1></center>\r\n"             \
                    "<hr><center>zia/1.0.0 (Gab is a monster)</center>\r\n" \
                    "</body>\r\n"                                           \
                    "</html>\r\n");
    return true;
}

void module::File::fillMimeType(const std::string &filepath, http::IResponse &response) const
{
    std::regex regex("\\.[^\\/]{1,}$");
    auto matching = std::regex_search(filepath, regex);
    if (matching == false) {
        response.headerParameter("Content-Type", "application/octet-stream");
        return;
    }
    std::sregex_token_iterator it(filepath.begin(), filepath.end(), regex);
    std::string extension(it->str().substr(1));
    auto find = mimetype.find(extension);
    if (find == mimetype.end())
        response.headerParameter("Content-Type", "application/octet-stream");
    else
        response.headerParameter("Content-Type", find->second);
}

bool module::File::execute(const net::IClient &client, http::IRequest &request, http::IResponse &response) noexcept
{
    auto path = this->m_rootFolder + "/" + request.route();
    boost::filesystem::path file(path);
    if (!boost::filesystem::exists(file))
        return responseError(404, "Not found", response);
    if (boost::filesystem::is_directory(file)) {
        path += "/index.html";
        file = boost::filesystem::path(path);
        if (!boost::filesystem::exists(file))
            return responseError(404, "Not found", response);
    }
    try {
        std::ifstream content(path);
        std::stringstream s;
        s << content.rdbuf();
        response.body(s.str());
        this->fillMimeType(path, response);
    }
    catch (const std::exception e) {
        return false;
    }
    return true;
}

bool module::File::beforePacked(const net::IClient &client, http::IResponse &response) noexcept
{
    return true;
}

bool module::File::beforeSend(const net::IClient &client, std::string &buffer) noexcept
{
    return true;
}

module::Api *factory()
{
    return new module::File();
}

BOOST_DLL_ALIAS(factory, create_module)
