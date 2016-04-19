#pragma once

#include <ht_refcounted_resourcemanager.h>

namespace Hatchit
{
    namespace Core
    {
        RefCountedResourceManager::RefCountedResourceManager() : m_resources() {}
        RefCountedResourceManager::~RefCountedResourceManager()
        {
            assert(m_resources.size() == 0);
        }

        template<typename ResourceType, typename... Args>
        inline ResourceType* RefCountedResourceManager::GetRawPointer(const Guid& ID, Args&&... arguments)
        {
            if (ID == Guid::Empty)
                return nullptr;

            //Create a typed name so two different types can use the same name
            //name += std::to_string(typeid(ResourceType).hash_code());

            RefCountedResourceManager& _instance = RefCountedResourceManager::GetInstance();

            std::map<Guid, void*>::iterator it = _instance.m_resources.find(ID);
            if (it == _instance.m_resources.end())
            {
                //resource not found.  Must allocate
                ResourceType* resource = new ResourceType(name);
                if (!resource->Initialize(std::forward<Args>(arguments)...))
                {
                    delete resource;
                    return nullptr;
                }
                _instance.m_resources.insert(std::make_pair(ID, resource));
            }

            return reinterpret_cast<ResourceType*>(_instance.m_resources[ID]);
        }

        template<typename ResourceType>
        inline void RefCountedResourceManager::ReleaseRawPointer(const Guid& ID)
        {
            RefCountedResourceManager& _instance = RefCountedResourceManager::GetInstance();

            std::map<Guid, void*>::iterator it = _instance.m_resources.find(ID);
            if (it != _instance.m_resources.end())
            {
                delete (reinterpret_cast<ResourceType*>(_instance.m_resources[ID]));

                _instance.m_resources.erase(it);
            }
        }
    }
}