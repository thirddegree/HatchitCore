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

//Handle Header includes
#include <stdint.h> //uint32_t typedef
#include <typeinfo>
#include <mutex>
#include <ht_guid.h>
#include <ht_platform.h> //HT_API

//Handle Inline includes
#include <ht_refcounted_resourcemanager.h> //ReleaseRawPointer

//RefCounted Header includes
#include <stdint.h> //uint32_t typedef
#include <string> //const std::string typedef
#include <ht_noncopy.h> //INonCopy interface
#include <ht_platform.h> //HT_API

//RefCounted Inline includes
#include <ht_refcounted_resourcemanager.h> //GetRawPointer

//Forward declaractions
namespace Hatchit
{
    namespace Core
    {
        template<typename VarType>
        class RefCounted;
    }
}

namespace Hatchit
{
    namespace Core
    {
        /**
        \class Handle<T>
        \ingroup HatchitCore
        \brief Smart pointer to Ref-counted classes

        Handle contains pointer to RefCounted class.  Handles reference counting
        and release of refcounted resources.
        **/
        template<typename VarType>
        class HT_API Handle
        {
        public:
            Handle();
            Handle(const Handle& rhs);
            Handle(Handle&& rhs);
            ~Handle();

            //Public Methods
            Handle& operator=(const Handle& rhs);
            Handle& operator=(Handle&& rhs);

            VarType* operator->() const;

            bool operator>(const Handle<VarType>& rhs) const;
            bool operator<(const Handle<VarType>& rhs) const;
            bool operator==(const Handle<VarType>& rhs) const;
            bool operator!=(const Handle<VarType>& rhs) const;

            template<typename NewResourceType>
            Handle<NewResourceType> DynamicCastHandle() const;

            template<typename NewResourceType>
            Handle<NewResourceType> StaticCastHandle() const;


            bool IsValid() const;
            void Release();

        private:
            friend class RefCounted<VarType>;

            template<typename NewVarType>
            friend class Handle;

            Handle(VarType* varPtr, uint32_t* refCounter, const Guid* name);

            //Private members
            VarType*    m_ptr;
            uint32_t*   m_refCount;
            const Guid* m_ID;

            mutable std::mutex m_mutex;
        };

        /**
        \class RefCounted<T>
        \ingroup HatchitCore
        \brief Resource managed class based on reference counting

        RefCounted class describes class that manages its memory via
        handles.  Once there are no handles left to the instance, it
        releases itself.
        **/
        template<typename VarType>
        class HT_API RefCounted : public INonCopy
        {
        public:
            RefCounted() = default;
            RefCounted(RefCounted&&) = default;
            virtual ~RefCounted() = default;

            //Public Methods
            RefCounted& operator=(RefCounted&&) = default;

            template <typename... Args>
            static Handle<VarType> GetHandle(std::string name, Args&&... args);

            template <typename... Args>
            static Handle<VarType> GetHandleAsync(Handle<VarType> _default, std::string name, Args&&... args);

        protected:
            friend class RefCountedResourceManager;

            RefCounted(Guid ID);

        private:
            uint32_t    m_refCount;
            const Guid  m_ID;
        };
    }
}

#include <ht_handle.inl>
#include <ht_refcounted.inl>
