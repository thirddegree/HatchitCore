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

#include <ht_threadvector.h>
#include <cassert>

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn ThreadsafeVector<T>::ThreadsafeVector()
        \brief Creates empty thread-safe vector.
        **/
        template <typename T>
        ThreadsafeVector<T>::ThreadsafeVector()
            : m_data(), m_mutex()
        {

        }

        /**
        \fn ThreadsafeVector<T>::ThreadsafeVector(const ThreadsafeVector<T>& other)
        \brief Creates copy of given Threadsafe vector
        **/
        template <typename T>
        ThreadsafeVector<T>::ThreadsafeVector(const ThreadsafeVector<T>& other)
        {
            std::lock_guard<std::mutex> lock(other.m_mutex);

            m_data = other.m_data;
        }

        /**
        \fn ThreadsafeVector<T>::ThreadsafeVector(ThreadsafeVector<T>&& other)
        \brief Moves data from given Threadsafe vector into new Threadsafe vector
        **/
        template <typename T>
        ThreadsafeVector<T>::ThreadsafeVector(ThreadsafeVector&& other)
        {
            std::lock_guard<std::mutex> lock(other.m_mutex);

            m_data = std::move(other.m_data);
        }

        /**
        \fn ThreadsafeVector<T> ThreadsafeVector<T>::operator=(const ThreadsafeVector<T>& other)
        \brief Copies data from one Threadsafe vector into current Threadsafe vector

        Copies data from one ThreadsafeVector into current ThreadsafeVector.
        One must be cautious when assigning Threadsafe objects to each other,
        as assignments of one object to itself will cause deadlock, and
        assignments of objects to each other concurrently may cause
        deadlock.
        **/
        template <typename T>
        ThreadsafeVector<T>& ThreadsafeVector<T>::operator= (const ThreadsafeVector<T>& other)
        {
            assert(this != &other);

            std::lock_guard<std::mutex> lockA(m_mutex);
            std::lock_guard<std::mutex> lockB(other.m_mutex);

            m_data = other.m_data;

            return *this;
        }


        /**
        \fn ThreadsafeVector<T> ThreadsafeVector<T>::operator=(ThreadsafeVector<T>&& other)
        \brief Moves data from temporary Threadsafe vector into current Threadsafe vector

        Moves data from temporary ThreadsafeVector into current ThreadsafeVector.
        One must be cautious when assigning Threadsafe objects to each other,
        as assignments of one object to itself will cause deadlock, and
        assignments of objects to each other concurrently may cause
        deadlock.
        **/
        template <typename T>
        ThreadsafeVector<T>& ThreadsafeVector<T>::operator=(ThreadsafeVector<T>&& other)
        {
            assert(this != &other);

            std::lock_guard<std::mutex> lockA(m_mutex);
            std::lock_guard<std::mutex> lockB(other.m_mutex);

            m_data = std::move(other.m_data);

            return *this;
        }
        
        /**
        \fn T& ThreadsafeVector<T>::operator[](size_t pos)
        \brief Returns a shared ptr copy to the element at specified location \a pos in ThreadsafeVector
        
        No bounds checking is performed.
        **/
        template <typename T>
        std::shared_ptr<T> ThreadsafeVector<T>::operator[](size_t pos)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_data.empty())
                throw std::exception();

            std::shared_ptr<T> const result = std::make_shared<T>(m_data.at(pos));

            return result;
        }

        /**
        \fn void ThreadsafeVector<T>::push_back(T _val)
        \brief Adds a new value \a _val to current ThreadsafeVector
        **/
        template <typename T>
        void ThreadsafeVector<T>::push_back(T _val)
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_data.push_back(std::move(_val));
        }

        /**
        \fn size_t ThreadsafeVector<T>::size() const
        \brief Returns the current number of elements in ThreadsafeVector
        **/
        template <typename T>
        size_t ThreadsafeVector<T>::size() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            return m_data.size();
        }
    }
}