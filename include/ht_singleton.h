/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
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

//Header includes
#include <ht_platform.h> //HT_API
#include <ht_noncopy.h> //INonCopy

//Inline includes
#include <type_traits> //std::is_default_constructable

namespace Hatchit
{
    namespace Core
    {
        /**
        \class Singleton<T>
        \ingroup HatchitCore
        \brief Describes class that has only one instance avialable globally.

        Describes class that has only one instance available globally.  Is
        unable to be copied or instantiated elsewhere.
        **/
        template <typename T>
        class HT_API Singleton : private INonCopy
        {
        public:
            static T& instance();

        protected:
            explicit Singleton<T>() = default;
        };
    }
}

#include <ht_singleton.inl>