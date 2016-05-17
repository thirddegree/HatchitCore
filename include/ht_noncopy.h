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

#include <ht_platform.h> //HT_API

/** \file ht_noncopy.h
* Noncopy Interface

* This file contains the interface definition
* for noncopyable classes
*/

namespace Hatchit
{
    namespace Core
    {
        /**
        \interface INonCopy
        \ingroup HatchitCore
        \brief Describes a class that cannot be copied.

        INonCopy describes the interface of a non-copyable class.
        Any attempt to copy an INonCopy will not compile.
        **/
        class HT_API INonCopy
        {
        protected:
            INonCopy() = default;
            virtual ~INonCopy() = default;

            INonCopy(const INonCopy&) = delete;
            INonCopy(INonCopy&&) = default;

            INonCopy& operator=(const INonCopy&) = delete;
            INonCopy& operator=(INonCopy&&) = default;
        };
    }
}