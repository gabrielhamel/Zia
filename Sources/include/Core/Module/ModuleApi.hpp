#ifndef IMODULE_API_HPP
#define IMODULE_API_HPP

namespace mod
{

struct ModuleApi
{
    /**
     * @brief Default destructor
     *
     */
    virtual ~ModuleApi() = default;

    virtual void sayHello();
};

} // namespace mod

#endif // IMODULE_API_HPP
