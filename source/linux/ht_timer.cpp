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

#include <ht_timer.h>

namespace Hatchit
{
    namespace Core
    {
        namespace Linux
        {
            /**
            \fn void Hatchit::Core::Linux::Timer::Timer()
            \brief Creates instance of timer, ready to be started
            **/
            Timer::Timer()
                : ITimer(),
                m_previous(0),
                m_stopped(true),
                m_totalTime(0),
                m_deltaTime(0.0f)
            {
            }
            
            /**
            \fn void Hatchit::Core::Linux::Timer::Start()
            \brief Starts tracking time from moment this function is called.

            Starts tracking time from moment this function is called.
            **/
            void Timer::Start()
            {
                if (m_stopped)
                {
                    clock_gettime(CLOCK_MONOTONIC_RAW, &m_previous);
                    m_stopped = false;
                }
            }
            
            /**
            \fn void Hatchit::Core::Linux::Timer::Stop()
            \brief Stops tracking timing information
            **/
            void Timer::Stop()
            {
                m_stopped = true;
            }

            /**
            \fn void Hatchit::Core::Linux::Timer::Reset()
            \brief Resets the timer data.  If timer is currently running, delta
            time will be calculated between the tick this function is called
            and the tick that Tick() is called.
            **/
            void Timer::Reset()
            {
                m_totalTime = 0;
                clock_gettime(CLOCK_MONOTONIC_RAW, &m_previous);
            }

            /**
            \fn void Hatchit::Core::Linux::Timer::Tick()
            \brief Recalculates the delta time and total time

            Recalculates the delta time between this tick and the last tick,
            or the last reset, depending on which happened more recently.
            Also recalculates the total time by accruing the calculated delta
            time into the total time.
            **/
            void Timer::Tick()
            {
                //If timer is stopped, we don't do anything
                if(m_stopped) {
                    m_deltaTime = 0.0;
                    return;
                }

                //Query the current time
                timespec current;
                clock_gettime(CLOCK_MONOTONIC_RAW, &current);
                
                timespec deltaTime;
                
                //timespec subtraction
                if ((current.tv_sec < m_previous.tv_sec) ||
                    ((current.tv_sec == m_previous.tv_sec) &&
                    (current.tv_nsec <= m_previous.tv_nsec)))
                {
                    deltaTime.tv_sec = deltaTime.tv_nsec = 0;
                }
                else
                {
                    deltaTime.tv_sec = current.tv_sec - m_previous.tv_sec;
                    if (current.tv_nsec < previous.tv_nsec)
                    {
                        deltaTime.tv_nsec = current.tv_nsec + 1000000000L - previous.tv_nsec;
                        deltaTime.tv_sec--;
                    }
                    else
                    {
                        deltaTime.tv_nsec = current.tv_nsec - previous.tv_nsec;
                    }
                }
                
                //Conversion to float
                m_deltaTime = static_cast<float>(
                    static_cast<double>(deltaTime.tv_sec) + 
                    static_cast<double>(deltaTime.tv_nsec) / 1000000000.0);
                    
                //timespec addition
                m_totalTime.tv_sec += deltaTime.tv_sec;
                m_totalTime.tv_nsec += deltaTime.tv_nsec;
                if (m_totalTime.tv_nsec >= 1000000000L)
                {
                    m_totalTime.tv_sec++;
                    m_totalTime.tv_nsec -= 1000000000L;
                }
                
                //Finally, set previous to current time.
                m_previous = current;
            }

            /**
            \fn float Hatchit::Core::Linux::Timer::TotalTime() const
            \brief Gets total time (in seconds) between when timer was started and last tick.
            **/
            float Timer::TotalTime() const
            {
                return static_cast<float>(
                    static_cast<double>(m_totalTime.tv_sec) +
                    static_cast<double>(m_totalTime.tv_nsec) / 1000000000.0);
            }

            /**
            \fn float Hatchit::Core::Linux::Timer::DeltaTime() const
            \brief Gets time (in seconds) between last two ticks of timer.
            **/
            float Timer::DeltaTime() const
            {
                return m_deltaTime;
            }
        }
    }
}
