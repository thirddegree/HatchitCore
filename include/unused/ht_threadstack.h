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
#include <stack> //std::stack<T>
#include <mutex> //std::mutex, std::lock_guard<T>
#include <memory> //std::shared_ptr<T>

//Inline includes
#include <cassert> //assert()

namespace Hatchit
{
    namespace Core
    {
        /**
        \class ThreadsafeStack<T>
        \ingroup HatchitCore
        \brief wrapper for std::stack that provides thread-safe functions
        **/
        template <typename T>
        class HT_API ThreadsafeStack
        {
        public:
            ThreadsafeStack();
            ThreadsafeStack(const ThreadsafeStack& other);
            ThreadsafeStack(ThreadsafeStack&& other);
            
            ThreadsafeStack& operator=(const ThreadsafeStack&);
            ThreadsafeStack& operator=(ThreadsafeStack&&);

            void push(T _val);

            std::shared_ptr<T> pop();
            void pop(T& _val);
            
            bool empty() const;
        private:
            std::stack<T>       m_data;
            mutable std::mutex  m_mutex;
        };
    }
}

#include <ht_threadstack.inl>