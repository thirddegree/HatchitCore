/**
**    Hatchit Engine
**    Copyright(c) 2016 Third-Degree
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

namespace Hatchit
{
    namespace Core
    {
        /**
        \interface Hatchit::Core::ITimer
        \ingroup HatchitCore
        \brief Interface to describe timer functionality

        Interface that describes the functionality of a timer.
        Used to link usability between a Windows timer and a
        Linux timer.
        **/
        class HT_API ITimer
        {
        protected:
            ITimer() = default;
            virtual ~ITimer() = default;

        public:
            virtual void Start() = 0;
            virtual void Tick() = 0;
            virtual void Stop() = 0;
            virtual void Reset() = 0;
            virtual float TotalTime() const = 0;
            virtual float DeltaTime() const = 0;
        };
    }    
}

#if defined(HT_SYS_LINUX)
#include <ht_linuxtimer.h>
#elif defined(HT_SYS_WINDOWS)
#include <ht_windowstimer.h>
#endif

namespace Hatchit
{
    namespace Core
    {
        #if defined(HT_SYS_LINUX)
        using Timer = Linux::Timer;
        #elif defined(HT_SYS_WINDOWS)
        using Timer = Windows::Timer;
        #endif
    }
}
