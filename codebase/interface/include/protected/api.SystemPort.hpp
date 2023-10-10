/**
 * @file      api.SystemPort.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_SYSTEMPORT_HPP_
#define API_SYSTEMPORT_HPP_

#include "api.Object.hpp"
#include "api.CpuProcessor.hpp"

namespace eoos
{
namespace api
{

/**
 * @class SystemPort
 * @brief Interface to be used by FreeRTOS ports and other RTOS ports.
 */
class SystemPort : public Object
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
    virtual ~SystemPort() = 0;

};

inline SystemPort::~SystemPort(){}

} // namespace api
} // namespace eoos
#endif // API_SYSTEMPORT_HPP_
