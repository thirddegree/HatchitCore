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

#include <ht_timer.h> //ITimer

#include <ht_platform.h> //HT_API
#include <time.h> //timespec

namespace Hatchit
{
    namespace Core
    {    
        namespace Linux
        {
            /**
            \class Hatchit::Core::Linux::Timer
            \ingroup HatchitCore
            \brief Class to manage tracking time.

            Class to manage tracking time.  Timer is specific to Linux
            **/
            class HT_API Timer : public ITimer
            {
            public:
                Timer();
                
                virtual ~Timer() = default;

                virtual void Start() override;

                virtual void Tick() override;

                virtual void Stop() override;

                virtual void Reset() override;

                virtual float ElapsedTime() const override;

                virtual float TotalTime() const override;

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
