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

#include <ht_platform.h>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace Hatchit
{
    namespace Core
    {
        /**
        \class ThreadsafeQueue<T>
        \ingroup HatchitCore
        \brief wrapper for std::queue that provides thread-safe functions
        */
        template <typename T>
        class HT_API ThreadsafeQueue
        {
        public:
            ThreadsafeQueue();
            ThreadsafeQueue(const ThreadsafeQueue& other);
            ThreadsafeQueue(ThreadsafeQueue&& other);

            ThreadsafeQueue& operator=(const ThreadsafeQueue& other);
            ThreadsafeQueue& operator=(ThreadsafeQueue&& other);

            void push(T _val);
            std::shared_ptr<T> wait_pop();
            void wait_pop(T& out);
            bool empty() const;

        private:
            std::queue<T>           m_data;
            mutable std::mutex      m_mutex;
            std::condition_variable m_condition;
        };
    }
}

#include <ht_threadqueue.inl>
