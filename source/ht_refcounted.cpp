#include <ht_refcounted.h>

namespace Hatchit
{
    namespace Core
    {
        RefCounted::RefCounted(std::string name) : m_name(std::move(name)) {}
    }
}