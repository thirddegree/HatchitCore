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

namespace Hatchit {

    namespace Core {

        Timer::Timer()
        {
            m_secPerTick = 0;
            m_deltaTime = 0.0;
            m_base = 0;
            m_paused = 0;
            m_previous = 0;
            m_current = 0;
            m_stopped = false;

            __int64 ticksPerSecond;
            QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond);

            m_secPerTick = 1.0 / static_cast<double>(ticksPerSecond);
        }

        void Timer::Start()
        {
            //Query for initial time
            QueryPerformanceCounter((LARGE_INTEGER*)&m_start);

            //If timer was previously stopped
            //we must accumulate the time it spent in that state
            if (m_stopped)
            {
                m_paused += (m_start - m_stop);

                m_previous = m_start;
                m_stop = 0;
                m_stopped = false;
            }

        }

        void Timer::Reset()
        {
            __int64 curTime;
            QueryPerformanceCounter((LARGE_INTEGER*)&curTime);

            m_base = curTime;
            m_previous = curTime;
            m_stop = 0;
            m_stopped = false;
        }

        void Timer::Stop()
        {
            if (!m_stopped)
            {
                //Query current time and set stop time
                __int64 curTime;
                QueryPerformanceCounter((LARGE_INTEGER*)&curTime);

                m_stop = curTime;
                m_stopped = true;
            }
        }

        void Timer::Tick()
        {
            //Don't do anything if the timer is stopped
            if (m_stopped) {
                m_deltaTime = 0.0;
                return;
            }

            //Query current time
            __int64 curTime;
            QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
            m_current = curTime;

            //Calculate the time difference between the current frame
            //and the previous. This is known as DeltaTime. After
            //we then setup for the next frame by setting previous to the current
            m_deltaTime = static_cast<double>(m_current - m_previous) * m_secPerTick;

            m_previous = m_current;
            
            //Also, make sure the delta time is never negative due to CPU error
            if (m_deltaTime < 0.0)
                m_deltaTime = 0.0;
        }

        float Timer::DeltaTime() const
        {
            return static_cast<float>(m_deltaTime);
        }

        float Timer::TotalTime() const
        {
            //If we happen to be stopped. We need to not include the time
            //we have spent paused. Thus, we subtract it from stop time, then take the different
            //(or elapsed) time since it started.
            if (m_stopped)
                return static_cast<float>(((m_stop - m_paused) - m_base)*m_secPerTick);
            //Otherwise, we want to take the time elapsed from the beginning (base) and the current
            //time. However, this will also include paused time. So we must again subtract this value.
            else
                return static_cast<float>(((m_current - m_paused) - m_base)*m_secPerTick);
        }

        float Timer::PausedTime() const
        {
            return static_cast<float>(m_paused * m_secPerTick);
        }

    }
}