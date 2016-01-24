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
            m_paused = {0};
            m_previous = {0};
            m_start = {0};
            m_stop = {0};
            m_current = {0};
            m_base = {0};
            m_stopped = false;
        }

        void Timer::Start()
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &m_start);

            if(m_stopped)
            {
                m_paused.tv_sec += (m_start.tv_sec - m_stop.tv_sec);
                m_paused.tv_nsec += (m_start.tv_nsec - m_stop.tv_nsec);

                m_previous = m_start;
                m_stop = {0};
                m_stopped = false;
            }
        }

        void Timer::Stop()
        {
            if(!m_stopped)
            {
                timespec current;
                clock_gettime(CLOCK_MONOTONIC_RAW, &current);

                m_stop = current;
                m_stopped = true;
            }
        }

        void Timer::Reset()
        {
            timespec current;
            clock_gettime(CLOCK_MONOTONIC_RAW, &current);

            m_base = current;
            m_previous = current;
            m_stop = {0};
            m_stopped = false;

            m_deltaTime = 0.0;
        }

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
            m_current = current;

            //Calculate the time difference between the current frame
            //and the previous. This is known as DelaTime. After
            //we then setup for the next frame by setting previous to the current
            double currentPart = static_cast<double>(m_current.tv_sec + (m_current.tv_nsec / 1000000000.0));
            double previousPart = static_cast<double>(m_previous.tv_sec + (m_previous.tv_nsec / 1000000000.0));

            m_deltaTime = currentPart - previousPart;

            m_previous = m_current;

            //make sure delta time is never negative due to CPU error
            if(m_deltaTime < 0.0)
                m_deltaTime = 0.0;
        }

        float Timer::TotalTime() const
        {
            //If we happen to be stopped. We need to exclude the time we have
            //spend paused. Thus, we subtract it from the stop time, then take the difference
            //(or elapsed) time since it started.
            double paused = static_cast<double>(m_paused.tv_sec + (m_paused.tv_nsec / 1000000000.0));
            double base = static_cast<double>(m_base.tv_sec + (m_paused.tv_nsec / 1000000000.0));
            if(m_stopped)
            {
                double stop = static_cast<double>(m_stop.tv_sec + (m_stop.tv_nsec / 1000000000.0));

                return static_cast<float>((stop - paused) - base);
            }
            else
            {
                double current = static_cast<double>(m_current.tv_sec + (m_current.tv_nsec / 1000000000.0));

                return static_cast<float>((current - paused) - base);
            }
        }

        float Timer::DeltaTime() const
        {
            return static_cast<float>(m_deltaTime);
        }

        float Timer::PausedTime() const
        {
            //timespec struct is defined as
            //tv_sec (the positive and greater than 1 part of time signature )
            //tv_nsec (the positive fraction of the time signature in nanoseconds)
            //To calculate the time in seconds we must add both parts in second units.
            return static_cast<float>((m_paused.tv_sec + (m_paused.tv_nsec / 1000000000.0)));
        }

    }
}
