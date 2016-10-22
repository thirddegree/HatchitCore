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
 * \file ht_linuxtimer.h
 * \brief Timer class definition
 * \author Matt Guerrette (direct3Dtutorials@gmail.com)
 * \author Third-Degree contibutors (https://github.com/thirddegree)
 *
 * This file contains definition for Linux Timer class
 */

#include <ht_platform.h>
#include <ht_timer.h>

#include <time.h>

namespace Hatchit
{
    namespace Core
    {    
        namespace Linux
        {
            /**
            * \class Timer
            * \brief Defines class to track elapsed time.
            *
            * Defines class to track elapsed time. Timer is specific to Linux
            **/
            class HT_API Timer : public ITimer
            {
            public:

                /**
                * \brief Creates instance of timer.
                *
                * Created instance must then be started.
                **/
                Timer();


                virtual ~Timer() = default;

                /**
                * \brief Starts tracking time from moment this function is called.
                *
                * Starts tracking time from moment this function is called.
                **/
                virtual void Start() override;

                /**
                * \brief Recalculates the delta time and total time
                *
                * Recalculates the delta time between this tick and the last tick,
                * or the last reset, depending on which happened more recently.
                * Also recalculates the total time by accruing the calculated delta
                * time into the total time.
                **/
                virtual void Tick() override;

                /**
                * \brief Stops timer
                *
                * Stops tracking timing information
                **/
                virtual void Stop() override;


                /**
                * \brief Resets the timer data.
                *
                * If timer is currently running, delta time will be calculated between
                * the tick this function is called and the tick that Tick() is called.
                **/
                virtual void Reset() override;

                /**
                * \brief Gets elapsed time (in seconds)
                *
                * Returns elapsed time (in seconds) between Start() and Stop() calls.
                */
                virtual float ElapsedTime() const override;

                /**
                * \brief Gets total time (in seconds)
                *
                * Returns total time between when timer was started and last tick.
                **/
                virtual float TotalTime() const override;

                /**
                * \brief Gets delta time (in seconds)
                *
                * Returns delta time (in seconds) between last two ticks of timer.
                **/
                virtual float DeltaTime() const override;

            private:
                timespec m_previous;
                timespec m_totalTime;
                bool m_stopped;
                
                float m_deltaTime;
            };
        }
    }
}
