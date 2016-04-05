#pragma once

#include <stdint.h>
#include <string>
#include <ht_platform.h>
#include <ht_noncopy.h>
#include <ht_refcounted_resourcemanager.h>

namespace Hatchit
{
    namespace Core
    {
        template<typename VarType>
        class HT_API Handle
        {
        public:
            Handle() = default;
            Handle(const Handle& rhs);
            Handle(Handle&& rhs) = default;
            ~Handle();
            Handle& operator=(const Handle& rhs);
            Handle& operator=(Handle&& rhs);

            VarType* operator->() const;

            template<typename NewResourceType>
            Handle<NewResourceType> CastHandle() const
            {
                NewResourceType* newPtr = dynamic_cast<NewResourceType*>(m_ptr);
                if (newPtr)
                    return Handle<NewResourceType>(newPtr, m_refCount, m_name);
                else
                    return Handle<NewResourceType>();
            }

            bool IsValid() const;

        private:
            friend class RefCounted;
            Handle(VarType* varPtr, uint32_t* refCounter, const std::string* m_name);
            VarType* m_ptr;
            uint32_t* m_refCount;
            const std::string* m_name;
        };


        class HT_API RefCounted : public INonCopy
        {
        public:
            RefCounted() = default;
            RefCounted(RefCounted&&) = default;
            virtual ~RefCounted() = default;

            RefCounted& operator=(RefCounted&&) = default;

            template<typename VarType>
            static typename std::enable_if<std::is_base_of<RefCounted, VarType>::value, Handle<VarType>>::type GetHandle(const std::string& name)
            {
                VarType* var = RefCountedResourceManager::GetRawPointer<VarType>(name);
                if (var)
                    return Handle<VarType>(var, &(var->m_refCount), &(var->m_name));
                else
                    return Handle<VarType>();
            }
        protected:
            friend class RefCountedResourceManager;
            RefCounted(std::string name);
        private:
            uint32_t m_refCount;
            const std::string m_name;
        };





        //TODO: Put inside an inline file
        template<typename VarType>
        Handle<VarType>::Handle(const Handle<VarType>& rhs)
            : m_ptr(rhs.m_ptr),
            m_refCount(rhs.m_refCount),
            m_name(rhs.m_name)
        {
            if (m_refCount)
                ++(*m_refCount);
        }

        template<typename VarType>
        Handle<VarType>::~Handle()
        {
            if (m_refCount && !--(*m_refCount))
            {
                //Delete object
                RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_name);
            }
        }

        template<typename VarType>
        Handle<VarType>& Handle<VarType>::operator=(const Handle<VarType>& rhs)
        {
            if (m_refCount && !--(*m_refCount))
            {
                //Delete object
                RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_name);
            }
            m_ptr = rhs.m_ptr;
            m_refCount = rhs.m_refCount;
            m_name = rhs.m_name;
            if (m_refCount)
                ++(*m_refCount);
        }

        template<typename VarType>
        Handle<VarType>& Handle<VarType>::operator=(Handle<VarType>&& rhs)
        {
            if (m_refCount && !--(*m_refCount))
            {
                //Delete object
                RefCountedResourceManager::ReleaseRawPoitner<VarType>(*m_name);
            }
            m_ptr = std::move(rhs.m_ptr);
            m_refCount = std::move(rhs.m_refCount);
            m_name = std::move(rhs.m_name);
        }

        template<typename VarType>
        VarType* Handle<VarType>::operator->()
        {
            return m_ptr;
        }

        template<typename VarType>
        bool Handle<VarType>::IsValid()
        {
            return m_ptr != nullptr;
        }

        template<typename VarType>
        Handle<VarType>::Handle(VarType* varPtr, uint32_t* refCount, const std::string* name)
            : m_ptr(varPtr),
            m_refCount(refCount),
            m_name(name)
        {
            if (m_refCount)
                ++(*m_refCount);
        }

    }
}