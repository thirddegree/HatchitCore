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
 * \file ht_singleton.h
 * \brief Singelton class definition
 * \author Matt Guerrette (direct3Dtutorials@gmail.com)
 * \author Third-Degree contributors (https://github.com/thirddegree)
 *
 * This file contains definition for Singleton class
 */

#include <ht_platform.h>
#include <ht_noncopy.h>

#include <type_traits>

namespace Hatchit
{
    namespace Core
    {
        /**
        * \class Singleton
        * \brief Describes class that has only one instance avialable globally.
        *
        * Describes class that has only one instance available globally.  Is
        * unable to be copied or instantiated elsewhere.
        **/
        template <typename T>
        class HT_API Singleton : private INonCopy
        {
        public:

            /**
            * \brief Provides reference to single instance of class
            *
            * Provides mutable reference to single instance of singleton class.
            **/
            static T& instance();

        protected:
            explicit Singleton<T>() = default;
        };
    }
}

#include <ht_singleton.inl>