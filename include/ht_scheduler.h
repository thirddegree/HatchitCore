/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
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
* \class Scheduler
* \ingroup HatchitCore
*
* \brief A manager that schedules and submits jobs to threads as they are available
*
* Supply this manager with function pointers (jobs) and it should schedule and sync these
* jobs appropriately across however many threads are on the hardware.
*/

#pragma once

#include "ht_singleton.h"

#include <thread>
#include <tuple>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>

namespace Hatchit {

    namespace Core {

        class HT_API IJob
        {
        public:
            virtual std::thread GetThread() = 0;
        };

        template<class... Ts>
        class HT_API Job : public IJob
        {
        public:
            template <class Func>
            Job(Func&& function)
            {
                m_function = function;
            }

            inline std::thread GetThread() override
            {
                return std::thread(m_function);
            }

        private:
            std::function<void()> m_function;
        };

        template class HT_API std::queue<IJob*>;

        class HT_API Scheduler : public Singleton<Scheduler>
        {       

        public:
            Scheduler();
            ~Scheduler();

            static void Initialize();

            template <class Func, class... Args>
            static void ScheduleJob(Func&& function, Args&&... arguments)
            {
                IJob* job = new Job<Args...>([&, arguments...]() { function(arguments...); threadEnded();  });

                addJob(job);
            }

            static void RunJobs();

        private:

            static uint32_t m_runningThreads;
            static uint32_t m_maxThreads;
            static std::queue<IJob*> m_jobs;

            static void addJob(IJob* job);
            static void threadEnded();
            
        };

    }

}