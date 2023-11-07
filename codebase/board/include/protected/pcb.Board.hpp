/**
 * @file      pcb.Board.hpp
 * @brief     EOOS printed circuit board
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef PCB_BOARD_HPP_
#define PCB_BOARD_HPP_

#include "lib.NonCopyable.hpp"
#include "lib.NoAllocator.hpp"
#include "lib.UniquePointer.hpp"
#include "drv.Usart.hpp"

namespace eoos
{
namespace pcb
{
    
/**
 * @class Board
 * @brief Target printed circuit board initalization.
 *
 * Object of the class must be alone in the system and configures target board on its construction.
 * All phases of system initialization must be done on the class constructor call 
 * and EOOS API must be accessible.
 */   
class Board : public lib::NonCopyable<lib::NoAllocator>
{

public:

    /**
     * @brief Constructor.
     */
    Board();

    /**
     * @brief Destructor.
     */
    virtual ~Board();

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Initializes USART.
     *
     * @return true if USART is configured.
     */    
    bool_t initializeUsart();
    
    /**
     * @brief Initializes USART.
     */    
    void deinitializeUsart();     
    
    /**
     * @brief Serial debug port.
     *
     * To use serial port for debugging, please use the jumper cap to connect the pin header of 
     * JMP2 (connect to PA9, PA10), and connect it to the computer through 
     * the USB interface of CN3.
     */    
    lib::UniquePointer<drv::Usart,lib::SmartPointerDeleter<drv::Usart>,lib::NoAllocator> usart_;

};

} // namespace pcb
} // namespace eoos

#endif // PCB_BOARD_HPP_
