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

/**
 * \file ht_timer.h
 * \brief Timer interface
 * \author Matt Guerrette (direct3Dtutorials@gmail.com)
 * \author Third-Degree contributors (https://github.com/thirddegree)
 *
 * This file contains definition for Timer interface
 */

#include <ht_platform.h>

namespace Hatchit
{
    namespace Core
    {
        /**
        * \interface Hatchit::Core::ITimer
        * \ingroup Core
        * \brief Interface to describe timer functionality
        *
        * Interface that describes the functionality of a timer.
        * Used to link usability between a Windows timer and a
        * Linux timer.
        **/
        class HT_API ITimer
        {
        protected:
            /**
            * \brief Creates instance of timer.
            *
            * Created instance must then be started.
            **/
            ITimer() = default;

            virtual ~ITimer() = default;

        public:

            /**
            * \brief Starts tracking time from moment this function is called.
            *
            * Starts tracking time from moment this function is called.
            **/
            virtual void Start() = 0;

            /**
            * \brief Calculates the delta time and total time
            *
            * Calculates the delta time between this tick and the last tick,
            * or the last reset, depending on which happened more recently.
            * Also recalculates the total time by accruing the calculated delta
            * time into the total time.
            **/
            virtual void Tick() = 0;

            /**
            * \brief Stops timer
            *
            * Stops tracking timing information
            **/
            virtual void Stop() = 0;

            /**
            * \brief Resets the timer data.
            *
            * If timer is currently running, delta time will be calculated between
            * the tick this function is called and the tick that Tick() is called.
            **/
            virtual void Reset() = 0;

            /**
            * \brief Gets elapsed time (in seconds)
            *
            * Returns elapsed time (in seconds) between Start() and Stop() calls.
            */
            virtual float ElapsedTime() const = 0;

            /**
            * \brief Gets total time (in seconds)
            *
            * Returns total time between when timer was started and last tick.
            **/
            virtual float TotalTime() const = 0;

            /**
            * \brief Gets delta time (in seconds)
            *
            * Returns delta time (in seconds) between last two ticks of timer.
            **/
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
