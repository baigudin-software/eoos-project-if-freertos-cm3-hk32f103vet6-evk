/**
 * @file      lib.AbstractList.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef LIB_ABSTRACTLIST_HPP_
#define LIB_ABSTRACTLIST_HPP_

#include "lib.NonCopyable.hpp"
#include "lib.Buffer.hpp"
#include "lib.LinkedNode.hpp"
#include "api.List.hpp"
#include "api.Queue.hpp"
#include "api.Iterable.hpp"

namespace eoos
{
namespace lib
{
    
/**
 * @class AbstractList<T,A>
 * @brief Abstract list class.
 *
 * @tparam T Data type of container element.
 * @tparam A Heap memory allocator class.
 */
template <typename T, class A = Allocator>
class AbstractList :
    public NonCopyable<A>,
    public api::List<T>,
    public api::Queue<T>,
    public api::Iterable<T>{

    typedef NonCopyable<A> Parent;
    typedef LinkedNode<T,A> Node;

public:
        
    using api::List<T>::getListIterator;

    /**
     * @brief Destructor.
     */
    virtual ~AbstractList()
    {
        AbstractList<T,A>::clear();
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1 and Defected Rule 9-3-3
    {
        return Parent::isConstructed();
    }

    /**
     * @copydoc eoos::api::List::add(T const&)
     */
    virtual bool_t add(T const& element)
    {
        size_t const lenght( getLength() );
        return isConstructed() ? addNode(static_cast<int32_t>(lenght), element) : false;
    }

    /**
     * @copydoc eoos::api::List::add(int32_t,T const&)
     */
    virtual bool_t add(int32_t const index, T const& element)
    {
        return isConstructed() ? addNode(index, element) : false;
    }

    /**
     * @copydoc eoos::api::List::clear()
     */
    virtual void clear()
    {
        if( isConstructed() )
        {
            size_t lenght( getLength() );
            while(true)
            {
                if(lenght == 0U)
                {
                    break;
                }
                Node* const node( getNodeByIndex(0) );
                static_cast<void>( removeNode(node) );
                lenght -= 1U;
            }
        }
    }

    /**
     * @copydoc eoos::api::List::removeFirst()
     */
    virtual bool_t removeFirst()
    {
        return remove(0);
    }

    /**
     * @copydoc eoos::api::List::removeLast()
     */
    virtual bool_t removeLast()
    {
        size_t const length( getLength() );
        return remove( static_cast<int32_t>(length) - 1 );
    }

    /**
     * @copydoc eoos::api::Queue::remove()
     */
    virtual bool_t remove()
    {
        return remove(0);
    }

    /**
     * @copydoc eoos::api::List::remove(int32_t)
     */
    virtual bool_t remove(int32_t const index)
    {
        return isConstructed() ? removeNode( getNodeByIndex(index) ) : false;
    }

    /**
     * @copydoc eoos::api::List::removeElement(T const&)
     */
    virtual bool_t removeElement(T const& element)
    {
        return isConstructed() ? removeNode( getNodeByElement(element) ) : false;
    }

    /**
     * @copydoc eoos::api::Queue::peek(T const&)
     */
    virtual T& peek()
    {
        return get(0);
    }

    /**
     * @copydoc eoos::api::List::getFirst()
     */
    virtual T& getFirst()
    {
        return get(0);
    }

    /**
     * @copydoc eoos::api::List::getLast()
     */
    virtual T& getLast()
    {
        size_t const length( getLength() );
        return get( static_cast<int32_t>(length) - 1 );
    }

    /**
     * @copydoc eoos::api::List::get()
     */
    virtual T& get(int32_t index)
    {   
        if( !isConstructed() )
        {
            return illegal_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
        }
        Node* const node( getNodeByIndex(index) );
        return (node != NULLPTR) ? node->getElement() : illegal_;
    }

    /**
     * @copydoc eoos::api::Collection::getLength()
     *
     * @todo Re-implement to return value of a member variable;
     */
    virtual size_t getLength() const
    {
        size_t length( 0U );
        if( isConstructed() )
        {
            length = (last_ == NULLPTR) ? 0U : ( static_cast<size_t>(last_->getIndex()) + 1U);
        }
        return length;
    }

    /**
     * @copydoc eoos::api::Collection::isEmpty()
     */
    virtual bool_t isEmpty() const
    {
        bool_t res( true );
        if( isConstructed() )
        {
            res =(last_ == NULLPTR) ? true : false;
        }
        return res;
    }

    /**
     * @copydoc eoos::api::IllegalValue::getIllegal()
     */
    virtual T const& getIllegal() const
    {
        return illegal_;
    }

    /**
     * @copydoc eoos::api::IllegalValue::setIllegal(T const&)
     */
    virtual void setIllegal(T const& value)
    {
        if( isConstructed() )
        {
            illegal_ = value;
        }
    }

    /**
     * @copydoc eoos::api::IllegalValue::isIllegal(T const&)
     */
    virtual bool_t isIllegal(T const& value) const
    {
        bool_t res( false );
        if( isConstructed() )
        {
            res = illegal_ == value;
        }
        return res;
    }

    /**
     * @copydoc eoos::api::List::getIndexOf(T const&)
     */
    virtual int32_t getIndexOf(T const& element) const
    {
        Node* const node( getNodeByElement(element) );
        return (node != NULLPTR) ? node->getIndex() : api::List<T>::ERROR_INDEX;
    }

    /**
     * @copydoc eoos::api::List::isIndex(T const&)
     */
    virtual bool_t isIndex(int32_t const index) const
    {
        bool_t res( false );
        if( 0 <= index )
        {
            if( static_cast<size_t>(index) < getLength() )
            {
                res = true;
            }
        }
        return res;
    }
    
    /**
     * @copydoc eoos::api::Iterable::getIterator()
     */
    virtual api::Iterator<T>* getIterator() ///< SCA MISRA-C++:2008 Defected Rule 9-3-3
    {
        return getListIterator(0);
    }

protected:

    /**
     * @brief Constructor.
     */
    AbstractList() 
        : NonCopyable<A>()
        , api::List<T>()
        , api::Queue<T>()
        , api::Iterable<T>()
        , illegal_()
        , last_(NULLPTR)
        , count_(0) {
    }

    /**
     * @brief Constructor.
     *
     * @note A passed element must be copied to an internal data structure of
     * this class by calling a copy constructor so that the element
     * might be invalidated after the function called.
     *
     * @param illegal An illegal element.
     */
    AbstractList(T const& illegal) 
        : NonCopyable<A>()
        , api::List<T>()
        , api::Queue<T>()
        , api::Iterable<T>()
        , illegal_(illegal)
        , last_(NULLPTR)
        , count_(0) {
    }

    /**
     * @brief Inserts new element to the specified position in this list.
     *
     * Given element will be copied to self nodes structure by a copy constructor calling.
     *
     * @param index   Position in this list.
     * @param element Inserting element.
     * @return True if element is inserted.
     *
     * @todo Shall re-implemented according MISRA-C++:2008 Rule 6–6–5 as the delete operator is used. 
     */
    bool_t addNode(int32_t const index, T const& element)
    {
        if(isIndexOutOfBounds(index))
        {
            return false;
        }
        Node* const node( new Node(element) );
        if( node == NULLPTR )
        {
            return false;
        }
        if( !node->isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            delete node;
            return false;
        }        
        if(last_ == NULLPTR)
        {
            last_ = node;
            count_++;
            return true;
        }
        if(index > 0)
        {
            Node* const after( getNodeByIndex(index - 1) );
            if(after == NULLPTR)
            {   ///< UT Justified Branch: SW dependency
                delete node;
                return false;
            }
            after->insertAfter(node);
            if(after == last_)
            {
                last_ = node;
            }
        }
        else
        {
            Node* const before( getNodeByIndex(0) );
            if(before == NULLPTR)
            {   ///< UT Justified Branch: SW dependency
                delete node;
                return false;
            }
            before->insertBefore(node);
        }
        count_++;
        return true;
    }

    /**
     * @brief Returns a node of this list by index.
     *
     * @param index Position in this list.
     * @return Pointer to the node of this list.
     */
    Node* getNodeByIndex(int32_t const index)
    {
        if( !isIndex(index) )
        {
            return NULLPTR;
        }
        size_t lenght( getLength() );
        if( static_cast<size_t>(index) == (lenght - 1U) )
        {
            return last_;
        }
        Node* node( last_->getNext() );
        for(int32_t i(0); i<index; i++)
        {
            node = node->getNext();
        }
        return node;
    }

    /**
     * @brief Returns a node of this list by element.
     *
     * @param element Reference to element.
     * @return Pointer to the node of this list.
     */
    Node* getNodeByElement(T const& element) const
    {
        Node* res( NULLPTR );
        size_t const len( getLength() );
        if(len != 0U)
        {
            Node* node( last_->getNext() );
            for(size_t i(0U); i<len; i++)
            {
                if(element != node->getElement())
                {
                    node = node->getNext();
                    continue;
                }
                res = node;
                break;
            } ///< UT Justified Line: Compiler dependency
        }
        return res;
    }

    /**
     * @brief Removes a node of this list.
     *
     * @param node Pointer to node.
     * @return True if a node is removed successfully.
     */
    bool_t removeNode(Node* const node)
    {
        if(node == NULLPTR)
        {
            return false;
        }
        if(node == last_)
        {
            if(getLength() == 1U)
            {
                last_ = NULLPTR;
            }
            else
            {
                last_ = last_->getPrevious();
            }
        }
        delete node;
        count_++;
        return true;
    }

    /**
     * @brief Tests if index is out of this list bounds.
     *
     * @param index Checking position in this list.
     * @return True if index is outed.
     */
    bool_t isIndexOutOfBounds(int32_t const index) const
    {
        if( index < 0 )
        {
            return true;
        }   ///< UT Justified Line: Compiler dependency
        else if( static_cast<size_t>(index) > getLength() )
        {
            return true;
        }   ///< UT Justified Line: Compiler dependency
        else
        {
            return false;
        }
    }

    /**
     * @brief Returns reference to self data value.
     *
     * @return Data value.
     */
    uint32_t& getReferenceToCount()
    {
        return count_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
    }

    /**
     * @brief Returns reference to self data value.
     *
     * @return Data value.
     */
    Node*& getReferenceToLast()
    {
        return last_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
    }

    /**
     * @brief Returns reference to self data value.
     *
     * @return Data value.
     */
    T& getReferenceToIllegal()
    {
        return illegal_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
    }

private:

    /**
     * @brief Illegal element of this list.
     */
    T illegal_;

    /**
     * @brief Last node of this list.
     */
    Node* last_;

    /**
     * @brief Number of changes in this list.
     */
    uint32_t count_;

};
        
} // namespace lib
} // namespace eoos
#endif // LIB_ABSTRACTLIST_HPP_
