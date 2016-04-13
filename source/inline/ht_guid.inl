#pragma once

#include <ht_guid.h>

namespace std
{
    inline size_t hash<Hatchit::Core::Guid>::operator()(const Hatchit::Core::Guid& guid) const
    {
        return guid.GetHashCode();
    }
}
