/**
 * @file      api.Supervisor.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_SUPERVISOR_HPP_
#define API_SUPERVISOR_HPP_

#include "api.Object.hpp"
#include "api.CpuProcessor.hpp"

namespace eoos
{
namespace api
{

/**
 * @class Supervisor
 * @brief System interface for supervisor calls of kernel, drivers, extentions, and etc.
 */
class Supervisor : public Object
{

public:

    /**
     * @brief Returns the system processor it is executed on.
     *
     * @return The HW processor.
     */
    virtual CpuProcessor& getProcessor() = 0;
    
protected:

    /**
     * @brief Destructor.
     */
    virtual ~Supervisor() = 0;

};

inline Supervisor::~Supervisor() {}

} // namespace api
} // namespace eoos
#endif // API_SUPERVISOR_HPP_
