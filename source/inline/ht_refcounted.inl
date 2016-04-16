#pragma once

#include <ht_refcounted.h>

namespace Hatchit
{
    namespace Core
    {
        template<typename VarType>
        Handle::Handle() : m_ptr(), m_refCount(), m_name() {}
    }
}