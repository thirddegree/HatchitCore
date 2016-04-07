#pragma once

#include <map>
#include <string>
#include <assert.h>
#include <ht_platform.h>
#include <ht_singleton.h>

namespace Hatchit
{
    namespace Core
    {
        class HT_API RefCountedResourceManager : public Singleton<RefCountedResourceManager>
        {
        public:
            ~RefCountedResourceManager()
            {
                assert(m_resources.size() == 0);
            }
            template<typename ResourceType, typename... Args>
            static ResourceType* GetRawPointer(std::string name, Args&&... arguments);

            template<typename ResourceType>
            static void ReleaseRawPointer(const std::string& name);

        private:
            static RefCountedResourceManager& GetInstance();

            std::map<std::string, void*> m_resources;
        };

        template<typename ResourceType, typename... Args>
        ResourceType* RefCountedResourceManager::GetRawPointer(std::string name, Args&&... arguments)
        {
            if (name.empty())
                return nullptr;

            //Create a typed name so two different types can use the same name
            name += std::to_string(typeid(ResourceType).hash_code());

            RefCountedResourceManager& _instance = RefCountedResourceManager::GetInstance();

            std::map<std::string, void*>::iterator it = _instance.m_resources.find(name);
            if (it == _instance.m_resources.end())
            {
                //resource not found.  Must allocate
                ResourceType* resource = new ResourceType(name, std::forward<Args>(arguments)...);
                _instance.m_resources.insert(std::make_pair(name, resource));
            }

            return reinterpret_cast<ResourceType*>(_instance.m_resources[name]);
        }

        template<typename ResourceType>
        void RefCountedResourceManager::ReleaseRawPointer(const std::string& name)
        {
            RefCountedResourceManager& _instance = RefCountedResourceManager::GetInstance();

            std::map<std::string, void*>::iterator it = _instance.m_resources.find(name);
            if (it != _instance.m_resources.end())
            {
                delete (reinterpret_cast<ResourceType*>(_instance.m_resources[name]));

                _instance.m_resources.erase(it);
            }
        }
    }
}