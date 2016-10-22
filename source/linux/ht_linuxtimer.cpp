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

/**
 * \file ht_linuxtimer.cpp
 * \brief Timer class implementation
 * \author Matt Guerrette (direct3Dtutorials@gmail.com)
 * \author Third-Degree contributors (https://github.com/thirddegree)
 *
 * This file contains implementation for Linux timer class
 */

/**
 * We need to include this first, so that there isn't a circular dependency with
 * the aliases used.
 */
#include <ht_timer.h>

namespace Hatchit
{
    namespace Core
    {
        namespace Linux
        {

            Timer::Timer()
                : ITimer(),
                m_previous(),
                m_totalTime(),
                m_stopped(true),
                m_deltaTime(0.0f)
            {

            }

            void Timer::Start()
            {
                if (m_stopped)
                {
                    clock_gettime(CLOCK_MONOTONIC_RAW, &m_previous);
                    m_stopped = false;
                }
            }

            void Timer::Stop()
            {
                m_stopped = true;
            }


            void Timer::Reset()
            {
                m_totalTime = timespec();
                clock_gettime(CLOCK_MONOTONIC_RAW, &m_previous);
            }

            void Timer::Tick()
            {
                //If timer is stopped, we don't do anything
                if(m_stopped) {
                    m_deltaTime = 0.0f;
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
                    if (current.tv_nsec < m_previous.tv_nsec)
                    {
                        deltaTime.tv_nsec = current.tv_nsec + 1000000000L - m_previous.tv_nsec;
                        deltaTime.tv_sec--;
                    }
                    else
                    {
                        deltaTime.tv_nsec = current.tv_nsec - m_previous.tv_nsec;
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

            float Timer::ElapsedTime() const
            {
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
                    if (current.tv_nsec < m_previous.tv_nsec)
                    {
                        deltaTime.tv_nsec = current.tv_nsec + 1000000000L - m_previous.tv_nsec;
                        deltaTime.tv_sec--;
                    }
                    else
                    {
                        deltaTime.tv_nsec = current.tv_nsec - m_previous.tv_nsec;
                    }
                }

                return static_cast<float>(
                        static_cast<double>(deltaTime.tv_sec) +
                        static_cast<double>(deltaTime.tv_nsec) / 1000000000.0);
            }

            float Timer::TotalTime() const
            {
                return static_cast<float>(
                    static_cast<double>(m_totalTime.tv_sec) +
                    static_cast<double>(m_totalTime.tv_nsec) / 1000000000.0);
            }

            float Timer::DeltaTime() const
            {
                return m_deltaTime;
            }
        }
    }
}
