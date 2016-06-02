/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
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

//Header Includes
#include <ht_platform.h> //HT_API
#include <ht_singleton.h> //Singleton<T>
#include <map> //std::map<T, U>

//Inline includes
#include <ht_guid.h> //Guid
#include <cassert> //assert()

namespace Hatchit
{
    namespace Core
    {
        /**
        \class RefCountedResourceManager
        \ingroup HatchitCore
        \brief Singleton that manages allocation and freeing of RefCounted resources.

        Singleton that manages allocation and freeing of RefCounted resources
        via Guid ID.
        **/
        class HT_API RefCountedResourceManager 
            : public Singleton<RefCountedResourceManager>
        {
        public:
            RefCountedResourceManager();
            ~RefCountedResourceManager();
            
            template<typename ResourceType, typename... Args>
            static ResourceType* GetRawPointer(
                const Guid& ID, 
                Args&&... arguments);

            template <typename ResourceType, typename... Args>
            static ResourceType* GetRawPointerUnitialized(const Guid& ID, Args&&... arguments);

            template<typename ResourceType>
            static void ReleaseRawPointer(const Guid& name);

        private:
            static RefCountedResourceManager& GetInstance();

            std::map<Guid, void*>     m_resources;
        };
    }
}

#include <ht_refcounted_resourcemanager.inl>