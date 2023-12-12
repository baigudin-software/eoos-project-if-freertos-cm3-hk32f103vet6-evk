/**
 * @file      api.StreamManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_STREAMMANAGER_HPP_
#define API_STREAMMANAGER_HPP_

#include "api.Object.hpp"
#include "api.OutStream.hpp"

namespace eoos
{
namespace api
{

/**
 * @class StreamManager
 * @brief Stream sub-system manager interface.
 */    
class StreamManager : public Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~StreamManager() = 0;
    
    /**
     * @brief Returns system output character stream.
     *
     * @return The system output character stream.
     */
    virtual OutStream<char_t>& getCout() = 0;

    /**
     * @brief Returns system error output character stream.
     *
     * @return The system error output character stream.
     */
    virtual OutStream<char_t>& getCerr() = 0;    

    /**
     * @brief Sets a new system output character stream.
     * 
     * @param cout A new stream to set.
     * @return True if the system output character stream is set.
     */
    virtual bool_t setCout(OutStream<char_t>& cout) = 0;

    /**
     * @brief Sets a new system error output character stream.
     *
     * @param cerr A new stream to set.
     * @return True if the system error output character stream is set.     
     */
    virtual bool_t setCerr(OutStream<char_t>& cerr) = 0;

    /**
     * @brief Resets the system output character stream to default.
     */
    virtual void resetCout() = 0;

    /**
     * @brief Resets the system error output character stream to default.
     */
    virtual void resetCerr() = 0;

};

inline StreamManager::~StreamManager() {}

} // namespace api
} // namespace eoos
#endif // API_STREAMMANAGER_HPP_
