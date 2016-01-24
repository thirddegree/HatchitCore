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

#include <ht_platform.h>
#include <time.h>

namespace Hatchit {

    namespace Core {

        class HT_API Timer
        {
        public:
            Timer();

            void Start();

            void Tick();

            void Stop();

            void Reset();

            float TotalTime() const;

            float DeltaTime() const;

            float PausedTime() const;

        private:
            timespec m_base;
            timespec m_start;
            timespec m_current;
            timespec m_previous;
            timespec m_stop;
            timespec m_paused;
            bool     m_stopped;
            double   m_deltaTime;
            /*__int64 m_base;
            __int64 m_start;
            __int64 m_current;
            __int64 m_previous;
            __int64 m_stop;
            __int64 m_paused;
            bool    m_stopped;

            double        m_secPerTick;
            double        m_deltaTime;*/
        };

    }
}
