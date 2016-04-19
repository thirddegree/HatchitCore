#pragma once

#include <ht_refcounted.h>

namespace Hatchit
{
    namespace Core
    {
        template<typename VarType>
        inline Handle<VarType>::Handle() : m_ptr(), m_refCount(), m_name() {}

        template<typename VarType>
        inline Handle<VarType>::Handle(const Handle<VarType>& rhs)
            : m_ptr(rhs.m_ptr),
            m_refCount(rhs.m_refCount),
            m_name(rhs.m_name)
        {
            if (m_refCount)
                ++(*m_refCount);
        }

        template<typename VarType>
        inline Handle<VarType>::Handle(Handle<VarType>&& rhs)
            : m_ptr(rhs.m_ptr),
            m_refCount(rhs.m_refCount),
            m_name(rhs.m_name)
        {
            rhs.m_ptr = nullptr;
            rhs.m_refCount = nullptr;
            rhs.m_name = nullptr;
        }

        template<typename VarType>
        inline Handle<VarType>::~Handle()
        {
            if (m_refCount && !--(*m_refCount))
            {
                RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_name);
            }
        }

        template<typename VarType>
        inline Handle<VarType>& Handle<VarType>::operator=(const Handle<VarType>& rhs)
        {
            if (rhs.m_refCount)
                ++(*rhs.m_refCount);

            if (m_refCount && !--(*m_refCount))
            {
                RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_name);
            }

            m_ptr = rhs.m_ptr;
            m_refCount = rhs.m_refCount;
            m_name = rhs.m_name;

            return *this;
        }

        template<typename VarType>
        inline Handle<VarType>& Handle<VarType>::operator=(Handle<VarType>&& rhs)
        {
            if (m_refCount && !--(*m_refCount))
            {
                RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_name);
            }
            m_ptr = std::move(rhs.m_ptr);
            m_refCount = std::move(rhs.m_refCount);
            m_name = std::move(rhs.m_name);

            rhs.m_ptr = nullptr;
            rhs.m_refCount = nullptr;
            rhs.m_name = nullptr;

            return *this;
        }

        template<typename VarType>
        inline VarType* Handle<VarType>::operator->() const
        {
            return m_ptr;
        }

        template<typename VarType>
        inline bool Handle<VarType>::operator>(const Handle<VarType>& rhs) const
        {
            return m_ptr > rhs.m_ptr;
        }

        template<typename VarType>
        inline bool Handle<VarType>::operator<(const Handle<VarType>& rhs) const
        {
            return m_ptr < rhs.m_ptr;
        }

        template<typename VarType>
        inline bool Handle<VarType>::operator==(const Handle<VarType>& rhs) const
        {
            return m_ptr == rhs.m_ptr;
        }

        template<typename VarType>
        inline bool Handle<VarType>::operator!=(const Handle<VarType>& rhs) const
        {
            return m_ptr != rhs.m_ptr;
        }

        template<typename VarType>
        template<typename NewResourceType>
        inline Handle<NewResourceType> Handle<VarType>::DynamicCastHandle() const
        {
            NewResourceType* newPtr = dynamic_cast<NewResourceType*>(m_ptr);
            if (newPtr)
                return Handle<NewResourceType>(newPtr, m_refCount, m_name);
            else
                return Handle<NewResourceType>();
        }

        template<typename VarType>
        template<typename NewResourceType>
        inline Handle<NewResourceType> Handle<VarType>::StaticCastHandle() const
        {
            NewResourceType* newPtr = static_cast<NewResourceType*>(m_ptr);
            return Handle<NewResourceType>(newPtr, m_refCount, m_name);
        }

        template<typename VarType>
        inline bool Handle<VarType>::IsValid() const
        {
            return m_ptr != nullptr;
        }

        template<typename VarType>
        inline void Handle<VarType>::Release()
        {
            //For time being, we force release the resource
            RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_name);
        
            //Ideally, we want to return to this solution
            //if (m_refCount && !--(*m_refCount))
            //{
            //    //Delete referenced counter
            //    RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_name);
            //}

            m_ptr = nullptr;
            m_refCount = nullptr;
            m_name = nullptr;
        }

        template<typename VarType>
        inline Handle<VarType>::Handle(VarType* varPtr, uint32_t* refCounter, const std::string* name)
            : m_ptr(varPtr),
            m_refCount(refCounter),
            m_name(name)
        {
            if (m_refCount)
                ++(*m_refCount);
        }
    }
}