/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
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

//Header includes
#include <ht_platform.h> //HT_API
#include <ht_singleton.h> //Singleton<T>
#include <stdint.h> //uint32_t
#include <queue> //std::queue<T>

//Inline includes
#include <functional> //std::function<T>

//Forward declarations
namespace std
{
    class thread;
}

namespace Hatchit
{
    namespace Core
    {
        /**
        \interface IJob
        \ingroup HatchitCore
        \brief Interface for threading job.
        **/
        class HT_API IJob
        {
        public:
            virtual ~IJob() = default;

            virtual std::thread GetThread() = 0;
        };

        /**
        \class Job
        \ingroup HatchitCore
        \brief Describes a function to be threaded.
        **/
        class HT_API Job : public IJob
        {
        public:
            Job(std::function<void()> function);

            std::thread GetThread() override;

        private:
            std::function<void()> m_function;
        };

        /**
        * \class Scheduler
        * \ingroup HatchitCore
        *
        * \brief A manager that schedules and submits jobs to threads as they are available
        *
        * Supply this manager with function pointers (jobs) and it should schedule and sync these
        * jobs appropriately across however many threads are on the hardware.
        */
        class HT_API Scheduler : public Singleton<Scheduler>
        {
        public:
            Scheduler();
            ~Scheduler();

            static void Initialize();

            template <class Func, class... Args>
            static void ScheduleJob(Func&& function, Args&&... arguments);

            static void RunJobs();

        private:
            uint32_t m_runningThreads;
            uint32_t m_maxThreads;
            std::queue<IJob*> m_jobs;

            static void AddJob(IJob* job);
            static void ThreadEnded();
        };
    }
}

#include <ht_scheduler.inl>
