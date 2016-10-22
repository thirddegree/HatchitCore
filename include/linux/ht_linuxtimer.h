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
