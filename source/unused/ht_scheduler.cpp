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

#include <ht_scheduler.h>

#include <thread> //std::thread
#include <ht_debug.h> //HT_DEBUG_PRINTF

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn Job::Job(std::function<void()> function)
        \brief Creates Threading job for given function
        **/
        Job::Job(std::function<void()> function)
            : m_function(std::move(function))
        {}

        /**
        \fn std::thread Job::GetThread()
        \brief Creates thread for job and returns created thread.
        **/
        std::thread Job::GetThread() 
        {
            return std::thread(m_function);
        }

        /**
        \fn Scheduler::Scheduler()
        \brief Initializes scheduler to begin managing threads.
        **/
        Scheduler::Scheduler()
            : m_runningThreads(0),
            m_maxThreads(0)
        {}

        /**
        \fn Scheduler::~Scheduler()
        \brief Releases members of scheduler.
        **/
        Scheduler::~Scheduler() = default;

        /**
        \fn void Scheduler::Initialize()
        \brief Initializes scheduler and sets max threads

        Initializes scheduler and sets max threads to capacity of hardware.
        **/
        void Scheduler::Initialize() 
        {
            Scheduler& _instance = Scheduler::instance();

            _instance.m_maxThreads = std::thread::hardware_concurrency();
        }

        /**
        \fn void Scheduler::RunJobs()
        \brief Begins running jobs in a threaded environment

        Will attempt to run jobs in a threaded environment.  May hang until
        all jobs begin running.
        **/
        void Scheduler::RunJobs()
        {
            Scheduler& _instance = Scheduler::instance();

            _instance.m_runningThreads = 0;
            while (_instance.m_jobs.size() > 0)
            {
                if (_instance.m_runningThreads == _instance.m_maxThreads)
                    continue;

                _instance.m_runningThreads++;
                HT_DEBUG_PRINTF("Running Threads - %u : ", _instance.m_runningThreads);

                //Get the next job's pointer and then pop it off
                IJob* nextJob = _instance.m_jobs.front();
                _instance.m_jobs.pop();

                std::thread jobThread = nextJob->GetThread();
                jobThread.detach();

                //Job has been scheduled, we can delete it
                delete nextJob;
            }
        }

        /**
        \fn void Scheduler::AddJob(IJob* job)
        \brief Adds a job to run in threaded environment.
        **/
        void Scheduler::AddJob(IJob* job)
        {
            Scheduler& _instance = Scheduler::instance();

            _instance.m_jobs.push(job);
        }

        /**
        \fn void Scheduler::ThreadEnded()
        \brief Function called once a thread ends to decrease running total.
        **/
        void Scheduler::ThreadEnded() 
        {
            Scheduler& _instance = Scheduler::instance();

            _instance.m_runningThreads--;
        }
    }

}
