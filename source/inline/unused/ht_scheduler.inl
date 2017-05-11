#pragma once

#include <ht_scheduler.h>

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn void Scheduler::SchedulerJob(T&& function, U&&... arguments)
        \brief Schedules job to be run in a threaded environment.
        **/
        template<class Func, class... Args>
        inline void Scheduler::ScheduleJob(Func&& function, Args&&... arguments)
        {
            IJob* job = new Job([&, arguments...]() { function(arguments...); ThreadEnded();  });

            AddJob(job);
        }
    }
}

