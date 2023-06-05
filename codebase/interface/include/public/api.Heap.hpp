/**
 * @file      api.Heap.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_HEAP_HPP_
#define API_HEAP_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{
    
/**
 * @class Heap
 * @brief Heap memory interface.
 */
class Heap : public Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~Heap() = 0;

    /**
     * @brief Allocates memory.
     *
     * @param size Required memory size in byte.
     * @param ptr  NULLPTR value becomes to allocate memory, and
     *             other given values are simply returned
     *             as memory address.
     * @return Pointer to allocated memory or NULLPTR.
     */
    virtual void* allocate(size_t size, void* ptr) = 0;

    /**
     * @brief Frees allocated memory.
     *
     * @param ptr Pointer to allocated memory.
     */
    virtual void free(void* ptr) = 0;

};

inline Heap::~Heap() {}

} // namespace api
} // namespace eoos
#endif // API_HEAP_HPP_
