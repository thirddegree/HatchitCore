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

#include <map>
#include <string>
#include <ht_platform.h>
#include <ht_singleton.h>

namespace Hatchit
{
    namespace Core
    {
        class HT_API RefCountedResourceManager : public Singleton<RefCountedResourceManager>
        {
        public:
            template<typename ResourceType>
            static ResourceType* GetRawPointer(std::string name);

            template<typename ResourceType>
            static void ReleaseRawPointer(const std::string& name);

        private:
            static RefCountedResourceManager& GetInstance();

            std::map<std::string, void*> m_resources;
        };

        template<typename ResourceType>
        ResourceType* RefCountedResourceManager::GetRawPointer(std::string name)
        {
            if (name.empty())
                return nullptr;

            //Create a typed name so two different types can use the same name
            std::string typedName = name + typeid(ResourceType).raw_name();

            RefCountedResourceManager& _instance = RefCountedResourceManager::GetInstance();

            std::map<std::string, void*>::iterator it = _instance.m_resources.find(typedName);
            if (it == _instance.m_resources.end())
            {
                //resource not found.  Must allocate
                ResourceType* resource = new ResourceType(name); //Give the untyped name to the constructor so we can work with the original filename
                _instance.m_resources.insert(std::make_pair(typedName, resource));
            }

            return reinterpret_cast<ResourceType*>(_instance.m_resources[typedName]);
        }

        template<typename ResourceType>
        void RefCountedResourceManager::ReleaseRawPointer(const std::string& name)
        {
            RefCountedResourceManager& _instance = RefCountedResourceManager::GetInstance();

            //Create a typed name so two different types can use the same name
            std::string typedName = name + typeid(ResourceType).raw_name();

            std::map<std::string, void*>::iterator it = _instance.m_resources.find(typedName);
            if (it != _instance.m_resources.end())
            {
                delete (reinterpret_cast<ResourceType*>(_instance.m_resources[typedName]));

                _instance.m_resources.erase(it);
            }
        }
    }
}