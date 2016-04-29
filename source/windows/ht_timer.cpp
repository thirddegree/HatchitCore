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
#undef max
#include <algorithm> //std::max

namespace Hatchit
{
    namespace Core
    {
        namespace Windows
        {
            /**
            \fn void Hatchit::Core::Windows::Timer::Timer()
            \brief Creates instance of timer, ready to be started
            **/
            Timer::Timer()
                : ITimer(),
                m_previous(0),
                m_stopped(true),
                m_totalTime(0),
                m_secPerTick(),
                m_deltaTime(0.0f)
            {
                __int64 ticksPerSecond;
                QueryPerformanceFrequency(
                    reinterpret_cast<LARGE_INTEGER*>(&ticksPerSecond));

                m_secPerTick = 1.0 / static_cast<double>(ticksPerSecond);
            }

            /**
            \fn void Hatchit::Core::Windows::Timer::Start()
            \brief Starts tracking time from moment this function is called.

            Starts tracking time from moment this function is called.
            **/
            void Timer::Start()
            {
                if (m_stopped)
                {
                    //Query for initial time
                    QueryPerformanceCounter(
                        reinterpret_cast<LARGE_INTEGER*>(&m_previous));
                    m_stopped = false;
                }
            }

            /**
            \fn void Hatchit::Core::Windows::Timer::Reset()
            \brief Resets the timer data.  If timer is currently running, delta
            time will be calculated between the tick this function is called
            and the tick that Tick() is called.
            **/
            void Timer::Reset()
            {
                m_totalTime = 0;
                QueryPerformanceCounter(
                    reinterpret_cast<LARGE_INTEGER*>(&m_previous));
            }

            /**
            \fn void Hatchit::Core::Windows::Timer::Stop()
            \brief Stops tracking timing information
            **/
            void Timer::Stop()
            {
                m_stopped = true;
            }

            /**
            \fn void Hatchit::Core::Windows::Timer::Tick()
            \brief Recalculates the delta time and total time

            Recalculates the delta time between this tick and the last tick,
            or the last reset, depending on which happened more recently.
            Also recalculates the total time by accruing the calculated delta
            time into the total time.
            **/
            void Timer::Tick()
            {
                //Don't do anything if the timer is stopped
                if (m_stopped) {
                    m_deltaTime = 0.0;
                    return;
                }

                //Query current time
                __int64 curTime;
                QueryPerformanceCounter(
                    reinterpret_cast<LARGE_INTEGER*>(&curTime));

                //Calculate the time difference between the current frame
                //and the previous. This is known as DeltaTime. After
                //we then setup for the next frame by 
                //setting previous to the current
                __int64 deltaTicks = curTime - m_previous;

                //Since converting between int and float is expensive,
                //we're gonna do the conversion every tick instead of every
                //request, since requests for delta time are likely to happen 
                //more than once per timer tick.
                m_deltaTime = std::max(
                    static_cast<float>(
                        static_cast<double>(deltaTicks) * m_secPerTick),
                    0.0f);

                m_totalTime += deltaTicks;

                m_previous = curTime;
            }

            /**
            \fn float Hatchit::Core::Windows::Timer::DeltaTime() const
            \brief Gets time (in seconds) between last two ticks of timer.
            **/
            float Timer::DeltaTime() const
            {
                return m_deltaTime;
            }

            /**
            \fn float Hatchit::Core::Windows::Timer::TotalTime() const
            \brief Gets total time (in seconds) between when timer was started and last tick.
            **/
            float Timer::TotalTime() const
            {
                return static_cast<float>(
                    static_cast<double>(m_totalTime) * m_secPerTick);
            }
        }
    }
}