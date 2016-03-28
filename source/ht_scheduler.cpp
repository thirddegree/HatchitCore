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

#include "ht_scheduler.h"

#include <iostream>

namespace Hatchit {

    namespace Core {

        uint32_t Scheduler::m_runningThreads = 0;
        uint32_t Scheduler::m_maxThreads = 0;
        
        std::queue<IJob*> Scheduler::m_jobs = {};

        Scheduler::Scheduler() 
        {
            m_runningThreads = 0;
            m_maxThreads = 0;
        }
        Scheduler::~Scheduler() {}

        void Scheduler::Initialize() 
        {
            m_maxThreads = std::thread::hardware_concurrency();
        }

        void Scheduler::RunJobs()
        {
            m_runningThreads = 0;
            while (m_jobs.size() > 0)
            {
                if (m_runningThreads == m_maxThreads)
                    continue;

                m_runningThreads++;
                std::cout << m_runningThreads << " : ";

                //Get the next job's pointer and then pop it off
                IJob* nextJob = m_jobs.front();
                m_jobs.pop();

                std::thread jobThread = nextJob->GetThread();
                jobThread.detach();

                //Job has been scheduled, we can delete it
                delete nextJob;
            }
        }

        void Scheduler::addJob(IJob* job)
        {
            m_jobs.push(job);
        }

        void Scheduler::threadEnded() 
        {
            m_runningThreads--;
        }
    }

}