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

/**
 * \file ht_singleton.inl
 * \brief Singleton class implementation
 * \author Matt Guerrette (direct3Dtutorials@gmail.com)
 * \author Third-Degree contributors (https://github.com/thirddegree)
 *
 * This file contains implementation for Singleton class
 */

#include <ht_singleton.h>

namespace Hatchit
{
    namespace Core
    {
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