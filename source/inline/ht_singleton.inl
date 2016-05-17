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

#pragma once

#include <ht_singleton.h>

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn T& Singleton<T>::instance()
        \brief Provides reference to single instance of class

        Provides mutable reference to single instance of singleton class.
        **/
        template<typename T>
        T& Singleton<T>::instance()
        {
            static_assert(std::is_default_constructible<T>::value,
                "T is required to be default constructable");
            static T _instance;
            
            return _instance;
        }
    }
}