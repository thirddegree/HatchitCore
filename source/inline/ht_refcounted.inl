#pragma once

#include <ht_refcounted.h>

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn Handle<VarType> RefCounted<VarType>::GetHandle<Args>(std::string ID, Args... args)
        \brief Grabs handle to ref counted class from ID.

        Gives handle to RefCounted instance based on given ID.  If a refcounted instance does not
        currently exist for the given ID, one will be instantiated and a handle for it will return.
        If instantiation fails (no allocation or Initialize fails), an empty handle will be returned.
        **/
        template<typename VarType>
        template<typename... Args>
        inline Handle<VarType> RefCounted<VarType>::GetHandle(std::string ID, Args&&... args)
        {
            VarType* var = RefCountedResourceManager::GetRawPointer<VarType, Args...>(std::move(ID), std::forward<Args>(args)...);
            if (var)
                return Handle<VarType>(var, &(var->m_refCount), &(var->m_name));
            else
                return Handle<VarType>();
        }

        template<typename VarType>
        inline RefCounted<VarType>::RefCounted(std::string name)
            : m_name(std::move(name)),
            m_refCount(0U)
        {}
    }
}