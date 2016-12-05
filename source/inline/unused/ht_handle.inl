#pragma once

#include <ht_resource.h>

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn Handle<T>::Handle()
        \brief Creates an invalid handle.
        **/
        template<typename VarType>
        inline Handle<VarType>::Handle() : m_ptr(), m_refCount(), m_ID() {}

        /**
        \fn Handle<T>::Handle(const Handle<T>& rhs)
        \brief Copies reference to resource and increments reference counter.
        **/
        template<typename VarType>
        inline Handle<VarType>::Handle(const Handle<VarType>& rhs)
            : m_ptr(rhs.m_ptr),
            m_refCount(rhs.m_refCount),
            m_ID(rhs.m_ID)
        {
            if (m_refCount)
                ++(*m_refCount);
        }

        /**
        \fn Handle<T>::Handle(Handle<T>&& rhs)
        \brief Moves reference from temp object to new handle.
        **/
        template<typename VarType>
        inline Handle<VarType>::Handle(Handle<VarType>&& rhs)
            : m_ptr(std::move(rhs.m_ptr)),
            m_refCount(std::move(rhs.m_refCount)),
            m_ID(std::move(rhs.m_ID))
        {
            rhs.m_ptr = nullptr;
            rhs.m_refCount = nullptr;
            rhs.m_ID = nullptr;
        }

        /**
        \fn Handle<T>::~Handle()
        \brief Decreases reference count of resource.

        Decreases reference count of resource.  If reference count reaches
        zero, then resource is released.
        **/
        template<typename VarType>
        inline Handle<VarType>::~Handle()
        {
            if (m_refCount && !--(*m_refCount))
            {
                RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_ID);
            }
        }

        /**
        \fn Handle<T>& Handle<T>::operator=(const Handle<T>& rhs)
        \brief Assigns handle to reference of \a rhs handle.

        Assigns handle to reference of \a rhs handle.  Reference counts are
        decremented for this handle and incremented for \a rhs.
        **/
        template<typename VarType>
        inline Handle<VarType>& Handle<VarType>::operator=(const Handle<VarType>& rhs)
        {
            if (rhs.m_refCount)
                ++(*rhs.m_refCount);

            if (m_refCount && !--(*m_refCount))
            {
                RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_ID);
            }

            m_ptr = rhs.m_ptr;
            m_refCount = rhs.m_refCount;
            m_ID = rhs.m_ID;

            return *this;
        }

        /**
        \fn Handle<T>& Handle<T>::operator=(Handle<T>&& rhs)
        \brief Assigns handle to reference of temporary handle.

        Assigns handle to reference of temporary handle.  Reference counts are
        decremented for this handle and unchanged for rhs.  Rhs is made an
        invalid handle.
        **/
        template<typename VarType>
        inline Handle<VarType>& Handle<VarType>::operator=(Handle<VarType>&& rhs)
        {
            if (m_refCount && !--(*m_refCount))
            {
                RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_ID);
            }
            m_ptr = std::move(rhs.m_ptr);
            m_refCount = std::move(rhs.m_refCount);
            m_ID = std::move(rhs.m_ID);

            rhs.m_ptr = nullptr;
            rhs.m_refCount = nullptr;
            rhs.m_ID = nullptr;

            return *this;
        }

        /**
        \fn T* Handle<T>::operator->() const
        \brief Returns pointer to internal type for function / member operators
        **/
        template<typename VarType>
        inline VarType* Handle<VarType>::operator->() const
        {
            return m_ptr;
        }

        /**
        \fn Handle<T>::operator>(const Handle<T>& rhs) const
        \brief Comparison function for sorting handles

        Comparison function for sorting handles.  Comparison is done
        via comparing pointers to members.
        **/
        template<typename VarType>
        inline bool Handle<VarType>::operator>(const Handle<VarType>& rhs) const
        {
            return m_ptr > rhs.m_ptr;
        }

        /**
        \fn Handle<T>::operator<(const Handle<T>& rhs) const
        \brief Comparison function for sorting handles

        Comparison function for sorting handles.  Comparison is done
        via comparing pointers to members.
        **/
        template<typename VarType>
        inline bool Handle<VarType>::operator<(const Handle<VarType>& rhs) const
        {
            return m_ptr < rhs.m_ptr;
        }

        /**
        \fn Handle<T>::operator==(const Handle<T>& rhs) const
        \brief Comparison function for sorting handles

        Comparison function for sorting handles.  Comparison is done
        via comparing pointers to members.
        **/
        template<typename VarType>
        inline bool Handle<VarType>::operator==(const Handle<VarType>& rhs) const
        {
            return m_ptr == rhs.m_ptr;
        }

        /**
        \fn Handle<T>::operator!=(const Handle<T>& rhs) const
        \brief Comparison function for sorting handles

        Comparison function for sorting handles.  Comparison is done
        via comparing pointers to members.
        **/
        template<typename VarType>
        inline bool Handle<VarType>::operator!=(const Handle<VarType>& rhs) const
        {
            return m_ptr != rhs.m_ptr;
        }


        /**
        \fn Handle<U> Handle<T>::DynamicCastHandle<U>() const
        \brief Attempts to dynamic cast handle from type T to type U.

        Attempts a dynamic cast of handle from type T to type U.  If successful,
        returns a handle of type U to the same resource.  If unsuccessful, returns
        invalid handle.
        **/
        template<typename VarType>
        template<typename NewResourceType>
        inline Handle<NewResourceType> Handle<VarType>::DynamicCastHandle() const
        {
            NewResourceType* newPtr = dynamic_cast<NewResourceType*>(m_ptr);
            if (newPtr)
                return Handle<NewResourceType>(newPtr, m_refCount, m_ID);
            else
                return Handle<NewResourceType>();
        }

        /**
        \fn Handle<U> Handle<T>::StaticCastHandle<U>() const
        \brief Performs a static cast from type T to type U.

        Performs a static cast from type T to type U.  Returns a handle of type
        U to the same resource.
        **/
        template<typename VarType>
        template<typename NewResourceType>
        inline Handle<NewResourceType> Handle<VarType>::StaticCastHandle() const
        {
            NewResourceType* newPtr = static_cast<NewResourceType*>(m_ptr);
            return Handle<NewResourceType>(newPtr, m_refCount, m_ID);
        }

        /**
        \fn bool Handle<T>::IsValid() const
        \brief Returns whether handle points to valid resource

        A simple test to see whether handle points to a valid resource or not.
        If IsValid passes, you may dereference the handle safely.
        **/
        template<typename VarType>
        inline bool Handle<VarType>::IsValid() const
        {
            return m_ptr != nullptr;
        }

        /**
        \fn void Handle<T>::Release()
        \brief Dereferences handle's values, as if the handle was deleted.

        Dereferences the handle's values so that the reference count to the
        currently pointed to object is decremented, as if the handle was deleted.
        \note: Currently forces the release of the resource.  This is to be fixed
        in a future update.
        **/
        template<typename VarType>
        inline void Handle<VarType>::Release()
        {
            //For time being, we force release the resource
            RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_ID);
        
            //Ideally, we want to return to this solution
            //if (m_refCount && !--(*m_refCount))
            //{
            //    //Delete referenced counter
            //    RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_ID);
            //}

            m_ptr = nullptr;
            m_refCount = nullptr;
            m_ID = nullptr;
        }

        /**
        \fn Handle<T>::Handle(
            T* varPtr, 
            uint32_t* refCounter, 
            const std::string* name)
        \brief Creates handle from raw pointer and pointers to 
            reference count and name.

        Creates handle from raw pointer and pointers to 
        reference counter and name.  varPtr must be a pointer to an object that
        derives from RefCounted.
        **/
        template<typename VarType>
        inline Handle<VarType>::Handle(VarType* varPtr, uint32_t* refCounter, const Guid* ID)
            : m_ptr(std::move(varPtr)),
            m_refCount(refCounter),
            m_ID(std::move(ID))
        {
            if (refCounter)
                ++(*refCounter);
        }
    }
}