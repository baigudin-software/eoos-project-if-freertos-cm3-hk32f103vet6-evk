/**
 * @file      api.OperatingSystem.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_OPERATINGSYSTEM_HPP_
#define API_OPERATINGSYSTEM_HPP_

#include "api.System.hpp"
#include "api.CpuProcessor.hpp"

namespace eoos
{
namespace api
{

/**
 * @class OperatingSystem
 * @brief The operating system interface.
 */
class OperatingSystem : public System
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
    virtual ~OperatingSystem() = 0;

};

inline OperatingSystem::~OperatingSystem(){}

} // namespace api
} // namespace eoos
#endif // API_OPERATINGSYSTEM_HPP_
