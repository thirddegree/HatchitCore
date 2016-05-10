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

#include <cassert>
#include <ht_debug.h>

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn ThreadsafeQueue<T>::ThreadsafeQueue()
        \brief Creates empty thread-safe queue.
        **/
        template <typename T>
        ThreadsafeQueue<T>::ThreadsafeQueue()
            : m_data(), m_mutex()
        {
            m_count = 0;
        }

        /**
        \fn ThreadsafeQueue<T>::ThreadsafeQueue(const ThreadsafeQueue<T>& other)
        \brief Creates copy of given ThreadsafeQueue.
        **/
        template <typename T>
        ThreadsafeQueue<T>::ThreadsafeQueue(const ThreadsafeQueue<T>& other)
        {
            std::lock_guard<std::mutex> lock(other.m_mutex);

            m_data = other.m_data;
        }

        /**
        \fn ThreadsafeQueue<T>::ThreadsafeQueue(ThreadsafeQueue<T>&& other)
        \brief Moves data from given ThreadsafeQueue into new ThreadsafeQueue.
        **/
        template <typename T>
        ThreadsafeQueue<T>::ThreadsafeQueue(ThreadsafeQueue<T>&& other)
        {
            std::lock_guard<std::mutex> lock(other.m_mutex);

            m_data = std::move(other.m_data);
        }

        /**
        \fn ThreadsafeQueue<T> ThreadsafeQueue<T>::operator=(const ThreadsafeQueue<T>& other)
        \brief Copies data from one ThreadsafeQueue
        into current ThreadsafeQueue

        Copies data from one ThreadsafeQueue into current ThreadsafeQueue.
        One must be cautious when assigning Threadsafe objects to each other,
        as assignments of one object to itself will cause deadlock, and
        assignments of objects to each other concurrently may cause
        deadlock.
        **/
        template <typename T>
        ThreadsafeQueue<T>& ThreadsafeQueue<T>::operator=(const ThreadsafeQueue<T>& other)
        {
            assert(this != &other);

            std::lock_guard<std::mutex> lockA(m_mutex);
            std::lock_guard<std::mutex> lockB(other.m_mutex);

            m_data = other.m_data;

            return *this;
        }

        /**
        \fn ThreadsafeQueue<T> ThreadsafeQueue<T>::operator=(ThreadsafeQueue<T>&& other)
        \brief Moves data from temportaty ThreadsafeQueue
        into current ThreadsafeQueue

        Moves data from temporary ThreadsafeQueue into current ThreadsafeQueue.
        One must be cautious when assigning Threadsafe objects to each other,
        as assignments of one object to itself will cause deadlock, and
        assignments of objects to each other concurrently may cause
        deadlock.
        **/
        template <typename T>
        ThreadsafeQueue<T>& ThreadsafeQueue<T>::operator=(ThreadsafeQueue&& other)
        {
            assert(this != &other);

            std::lock_guard<std::mutex> lockA(m_mutex);
            std::lock_guard<std::mutex> lockB(other.m_mutex);

            m_data = std::move(other.m_data);

            return *this;
        }

        /**
        \fn void ThreadsafeQueue<T>::push(T _val)
        \brief Adds new value \a _val to current ThreadsafeQueue.
        **/
        template <typename T>
        void ThreadsafeQueue<T>::push(T _val)
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_data.push(std::move(_val));
        
            m_count++;

            m_cv.notify_one();
        }

        /**
        \fn std::shared_ptr<T> ThreadsafeQueue<T>::pop()
        \brief Pops off first element in queue, and returns a shared ptr to temp copy of it.
        **/
        template <typename T>
        std::shared_ptr<T> ThreadsafeQueue<T>::pop()
        {
            //Wait until there is a job that has been added to the queue
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait(lock, [this]() { return m_count > 0; });
            
            if (m_data.empty())
            {
                throw std::exception();
            }

            std::shared_ptr<T> const result = std::make_shared<T>(m_data.front());
            m_data.pop();

            m_count--;

            return result;
        }

        /**
        \fn void ThreadsafeQueue<T>::pop(T& out)
        \brief Removes last entry in queue and moves it into /a out param.
        **/
        template <typename T>
        void ThreadsafeQueue<T>::pop(T& out)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_data.empty())
                throw std::exception();

            out = m_data.front();
            m_data.pop();
        }

        /**
        \fn bool ThreadsafeQueue<T>::empty() const
        \brief Returns whether queue contains no members.
        **/
        template <typename T>
        bool ThreadsafeQueue<T>::empty() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            return m_data.empty();
        }
    }
}