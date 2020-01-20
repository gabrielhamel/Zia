#ifndef IMODULE_API_HPP
#define IMODULE_API_HPP

#include "IResponse.hpp"
#include "IRequest.hpp"

namespace mod
{

struct ModuleApi
{
    /**
     * @brief Default destructor
     */
    virtual ~ModuleApi() = default;

    /**
     * @brief Respond to an request
     */
    std::unique_ptr<http::IResponse> request(const http::IRequest &request);
};

} // namespace mod

#endif // IMODULE_API_HPP
