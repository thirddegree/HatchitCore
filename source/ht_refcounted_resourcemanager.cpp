#include <ht_refcounted_resourcemanager.h>

namespace Hatchit
{
    namespace Core
    {
        RefCountedResourceManager& RefCountedResourceManager::GetInstance()
        {
            return RefCountedResourceManager::instance();
        }
    }
}