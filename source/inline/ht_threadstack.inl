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

#include <ht_threadstack.h>

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn ThreadsafeStack<T>::ThreadsafeStack()
        \brief Creates empty thread-safe stack.
        **/
        template<typename T>
        ThreadsafeStack<T>::ThreadsafeStack()
            : m_data(),
            m_mutex() {}

        /**
        \fn ThreadsafeStack<T>::ThreadsafeStack(const ThreadsafeStack<T>& other)
        \brief Creates copy of given ThreadsafeStack.
        **/
        template<typename T>
        ThreadsafeStack<T>::ThreadsafeStack(const ThreadsafeStack<T>& other)
        {
            std::lock_guard<std::mutex> lock(other.m_mutex);

            m_data = other.data;
        }

        /**
        \fn ThreadsafeStack<T>::ThreadsafeStack(ThreadsafeStack<T>&& other)
        \brief Moves data from given Threadsafe stack 
            into new ThreadsafeStack<T>
        **/
        template<typename T>
        ThreadsafeStack<T>::ThreadsafeStack(ThreadsafeStack<T>&& other)
        {
            //NOTE: I don't think we need this lock, how else do you get
            //a reference to an lreference for another thread?
            std::lock_guard<std::mutex> lockB(other.m_mutex);

            m_data = std::move(other.m_data);
        }

        /**
        \fn ThreadsafeStack<T> ThreadsafeStack<T>::operator=(const ThreadsafeStack<T>& other)
        \brief Copies data from one ThreadsafeStack 
            into current ThreadsafeStack

        Copies data from one ThreadsafeStack into current ThreadsafeStack.
        One must be cautious when assigning Threadsafe objects to each other,
        as assignments of one object to itself will cause deadlock, and
        assignments of objects to each other concurrently may cause
        deadlock.
        **/
        template<typename T>
        ThreadsafeStack<T>& ThreadsafeStack<T>::operator=(
            const ThreadsafeStack<T>& other)
        {
            assert(this != &other); //Will cause deadlock!
            std::lock_guard<std::mutex> lockA(m_mutex);
            std::lock_guard<std::mutex> lockB(other.m_mutex);

            m_data = other.m_data;

            return *this;
        }

        /**
        \fn ThreadsafeStack<T> ThreadsafeStack<T>::operator=(ThreadsafeStack<T>&& other)
        \brief Moves data from temportaty ThreadsafeStack
        into current ThreadsafeStack

        Moves data from temporary ThreadsafeStack into current ThreadsafeStack.
        One must be cautious when assigning Threadsafe objects to each other,
        as assignments of one object to itself will cause deadlock, and
        assignments of objects to each other concurrently may cause
        deadlock.
        **/
        template<typename T>
        ThreadsafeStack<T>& ThreadsafeStack<T>::operator=(
            ThreadsafeStack<T>&& other)
        {
            assert(this != &other); //Will cause deadlock!
            std::lock_guard<std::mutex> lockA(m_mutex);
            std::lock_guard<std::mutex> lockB(other.m_mutex);

            m_data = std::move(other.m_data);

            return *this;
        }

        /**
        \fn void ThreadsafeStack<T>::push(T _val)
        \brief Adds new value \a _val to current ThreadsafeStack.
        **/
        template<typename T>
        void ThreadsafeStack<T>::push(T _val)
        {
            std::lock_guard<std::mutex> lockA(m_mutex);

            m_data.push(std::move(_val));
        }

        /**
        \fn std::shared_ptr<T> ThreadsafeStack<T>::pop()
        \brief Pops off last element in stack, and returns shared ptr to
        temp copy of it.

        Returns a temporary copy of the last element in the stack.  The
        last data member will also be removed from the data structure.
        **/
        template<typename T>
        std::shared_ptr<T> ThreadsafeStack<T>::pop()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_data.empty())
                throw std::exception();

            std::shared_ptr<T> const result = std::make_shared<T>(m_data.top());
            m_data.pop();

            return result;
        }

        /**
        \fn void ThreadsafeStack<T>::pop(T& out)
        \brief Removes last entry in stack and moves it into /a out param.
        **/
        template<typename T>
        void ThreadsafeStack<T>::pop(T& out)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_data.empty())
                throw std::exception();

            out = m_data.top();
            m_data.pop();
        }

        /**
        \fn bool ThreadsafeStack<T>::empty() const
        \brief Returns whether stack contains no members.
        **/
        template<typename T>
        bool ThreadsafeStack<T>::empty() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            return m_data.empty();
        }
    }
}
