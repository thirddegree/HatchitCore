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

#include <ht_scopedthread.h>

#include <stdexcept> //std::logic_error

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn ScopedThread::ScopedThread(std::thread _t)
        \brief Creates scoped thread given std::thread t.
        **/
        ScopedThread::ScopedThread(std::thread _t)
            : t(std::move(t))
        {
            if(!t.joinable())
                throw std::logic_error("No thread");
        }

        /**
        \fn ScopedThread::~ScopedThread()
        \brief Joins internal thread while scoped thread is being deleted
        **/
        ScopedThread::~ScopedThread()
        {
            t.join();
        }
    }
}
