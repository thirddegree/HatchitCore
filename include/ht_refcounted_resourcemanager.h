#pragma once

#include <map>
#include <string>
#include <typeinfo>
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