/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
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

#include <ht_refcounted_resourcemanager.h>

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn RefCountedResourceManager& RefCountedResourceManager::GetInstance()
        \brief Returns singleton instance to RefCountedResourceManager.

        Returns singleton instance to RefCountedResourceManager.  This function
        allows the instance to be localized to Core dll instead of calling dll.
        **/
        RefCountedResourceManager& RefCountedResourceManager::GetInstance()
        {
            return RefCountedResourceManager::instance();
        }
    }
}