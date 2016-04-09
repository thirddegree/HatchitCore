/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#pragma once

#include <stdint.h>
#include <string>
#include <ht_platform.h>
#include <ht_noncopy.h>
#include <ht_refcounted_resourcemanager.h>
#include <ht_string.h>

namespace Hatchit
{
    namespace Core
    {
        template<typename VarType>
        class RefCounted;

        template<typename VarType>
        class Handle
        {
        private:

            VarType* m_ptr;
            uint32_t* m_refCount;
            const std::string* m_name;

        public:
            Handle()
                : m_ptr(),
                m_refCount(),
                m_name() {};

            Handle(const Handle& rhs)
                : m_ptr(rhs.m_ptr),
                m_refCount(rhs.m_refCount),
                m_name(rhs.m_name)
            {
                if (m_refCount)
                    ++(*m_refCount);
            }

            Handle(Handle&& rhs) :
                m_ptr(rhs.m_ptr),
                m_refCount(rhs.m_refCount),
                m_name(rhs.m_name)
            {
                rhs.m_ptr = nullptr;
                rhs.m_refCount = nullptr;
                rhs.m_name = nullptr;
            }

            ~Handle()
            {
                if (m_refCount && !--(*m_refCount))
                {
                    //Delete object
                    RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_name);
                }
            }

            Handle& operator=(const Handle& rhs)
            {
                
                if (rhs.m_refCount)
                    ++(*rhs.m_refCount);

                if (m_refCount && !--(*m_refCount))
                {
                    //Delete object
                    RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_name);
                }
                m_ptr = rhs.m_ptr;
                m_refCount = rhs.m_refCount;
                m_name = rhs.m_name;

                return *this;
            }

            Handle& operator=(Handle&& rhs)
            {
                
                if (m_refCount && !--(*m_refCount))
                {
                    //Delete object
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

            VarType* operator->() const
            {
                return m_ptr;
            }

            bool operator>(const Handle<VarType>& rhs) const
            {
                return m_ptr > rhs.m_ptr;
            }
            bool operator<(const Handle<VarType>& rhs) const
            {
                return m_ptr < rhs.m_ptr;
            }
            bool operator==(const Handle<VarType>& rhs) const
            {
                return m_ptr == rhs.m_ptr;
            }
            bool operator!=(const Handle<VarType>& rhs) const
            {
                return m_ptr != rhs.m_ptr;
            }

            template<typename NewResourceType>
            Handle<NewResourceType> DynamicCastHandle() const
            {
                NewResourceType* newPtr = dynamic_cast<NewResourceType*>(m_ptr);
                if (newPtr)
                    return Handle<NewResourceType>(newPtr, m_refCount, m_name);
                else
                    return Handle<NewResourceType>();
            }

            template<typename NewResourceType>
            Handle<NewResourceType> StaticCastHandle() const
            {
                NewResourceType* newPtr = static_cast<NewResourceType*>(m_ptr);
                uint32_t* newRefCount = m_refCount;
                const std::string* newName = m_name;
                return Handle<NewResourceType>(newPtr, newRefCount, newName);
            }

            bool IsValid() const
            {
                return m_ptr != nullptr;
            }

            void Release()
            {
                if (m_refCount && !--(*m_refCount))
                {
                    //Delete referenced counter
                    RefCountedResourceManager::ReleaseRawPointer<VarType>(*m_name);
                }

                m_ptr = nullptr;
                m_refCount = nullptr;
                m_name = nullptr;
            }

        private:
            friend class RefCounted<VarType>;

            template<typename NewVarType>
            friend class Handle;

            Handle(VarType* varPtr, uint32_t* refCounter, const std::string* name)
                : m_ptr(varPtr),
                m_refCount(refCounter),
                m_name(name)
            {
                if (m_refCount)
                    ++(*m_refCount);
            }
        };

        template<typename VarType>
        class RefCounted : public INonCopy
        {
        public:
            RefCounted() = default;
            RefCounted(RefCounted&&) = default;
            virtual ~RefCounted() = default;

            RefCounted& operator=(RefCounted&&) = default;

            template<typename... Args>
            static Handle<VarType> GetHandle(std::string ID, Args&&... args)
            {
                VarType* var = RefCountedResourceManager::GetRawPointer<VarType, Args...>(std::move(ID), std::forward<Args>(args)...);
                if (var)
                    return Handle<VarType>(var, &(var->m_refCount), &(var->m_name));
                else
                    return Handle<VarType>();
            }
            
        protected:
            friend class RefCountedResourceManager;

            RefCounted(std::string name)
                : m_name(std::move(name)),
                m_refCount(0U) {}

        private:
            uint32_t m_refCount;
            const std::string m_name;
        };
    }
}
