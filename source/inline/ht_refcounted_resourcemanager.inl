#pragma once

#include <ht_refcounted_resourcemanager.h>

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn RefCountedResourceManager::RefCountedResourceManager()
        \brief Initializes internal storage system for 
        storing RefCounted objects
        **/
        inline RefCountedResourceManager::RefCountedResourceManager()
            : m_resources() {}

        /**
        \fn RefCountedResourceManager::~RefCountedResourceManager()
        \brief Releases any unreleased refcounted objects.

        Releases any unreleased refcounted objects.  This should ideally NEVER
        happen.  An assert will fire if any refcounted objects are still
        alive at this point.
        **/
        inline RefCountedResourceManager::~RefCountedResourceManager()
        {
            assert(m_resources.size() == 0);
        }

        /**
        \fn template<typename T, typename... Args>
            T* RefCountedResourceManager::GetRawPointer<T, Args>(
            const Guid& ID,
            Args&&... arguments)
        \brief Grabs raw pointer associated with ID, may initialize with given
        arguments

        Grabs the raw pointer of type T with given Guid ID.  If no raw pointer
        is found with ID, one is created and initialized with given
        arguments.  Then it is stored inside RefCountedResourceManager for
        later accessibility.
        **/
        template<typename ResourceType, typename... Args>
        inline ResourceType* RefCountedResourceManager::GetRawPointer(const Guid& ID, Args&&... arguments)
        {
            if (ID == Guid::GetEmpty())
                return nullptr;

            //Create a typed name so two different types can use the same name
            //name += std::to_string(typeid(ResourceType).hash_code());

            RefCountedResourceManager& _instance = RefCountedResourceManager::GetInstance();

            std::map<Guid, void*>::iterator it = _instance.m_resources.find(ID);
            if (it == _instance.m_resources.end())
            {
                //resource not found.  Must allocate
                ResourceType* resource = new ResourceType(ID);
                if (!resource->Initialize(std::forward<Args>(arguments)...))
                {
                    delete resource;
                    return nullptr;
                }
                _instance.m_resources.insert(std::make_pair(ID, resource));
            }

            return reinterpret_cast<ResourceType*>(_instance.m_resources[ID]);
        }

        template<typename ResourceType, typename ...Args>
        inline ResourceType * RefCountedResourceManager::GetRawPointerUnitialized(const Guid & ID, Args && ...arguments)
        {
            if (ID == Guid::GetEmpty())
                return nullptr;

            RefCountedResourceManager& _instance = RefCountedResourceManager::GetInstance();

            std::map<Guid, void*>::iterator it = _instance.m_resources.find(ID);
            if (it == _instance.m_resources.end())
            {
                //resource not found.  Must allocate
                ResourceType* resource = new ResourceType(ID);
               
                _instance.m_resources.insert(std::make_pair(ID, resource));
            }

            return reinterpret_cast<ResourceType*>(_instance.m_resources[ID]);
        }

        /**
        \fn template<typename T>
            void RefCountedResourceManager::ReleaseRawPointer<T>(
            const Guid& ID)
        \brief Releases raw pointer stored inside ResourceManager with given ID

        Releases raw pointer stored inside ResourceManager with given ID.
        Destructor called is synonymous with T.
        **/
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