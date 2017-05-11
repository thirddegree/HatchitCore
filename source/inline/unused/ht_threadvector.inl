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

/**
 * \file ht_threadvector.inl
 * \brief ThreadVector class implementation
 * \author Matt Guerrette (direct3Dtutorials@gmail.com)
 * \author Third-Degree contributors (https://github.com/thirddegree)
 *
 * This file contains implementation for ThreadVector class
 */

#include <ht_threadvector.h>

namespace Hatchit
{
    namespace Core
    {
        template <typename T>
        ThreadsafeVector<T>::ThreadsafeVector()
            : m_data(), m_mutex()
        {

        }

        template <typename T>
        ThreadsafeVector<T>::ThreadsafeVector(const ThreadsafeVector<T>& other)
        {
            std::lock_guard<std::mutex> lock(other.m_mutex);

            m_data = other.m_data;
        }

        template <typename T>
        ThreadsafeVector<T>::ThreadsafeVector(ThreadsafeVector&& other)
        {
            std::lock_guard<std::mutex> lock(other.m_mutex);

            m_data = std::move(other.m_data);
        }

        template <typename T>
        ThreadsafeVector<T>& ThreadsafeVector<T>::operator=(const ThreadsafeVector<T>& other)
        {
            assert(this != &other);

            std::lock_guard<std::mutex> lockA(m_mutex);
            std::lock_guard<std::mutex> lockB(other.m_mutex);

            m_data = other.m_data;

            return *this;
        }

        template <typename T>
        ThreadsafeVector<T>& ThreadsafeVector<T>::operator=(ThreadsafeVector<T>&& other)
        {
            assert(this != &other);

            std::lock_guard<std::mutex> lockA(m_mutex);
            std::lock_guard<std::mutex> lockB(other.m_mutex);

            m_data = std::move(other.m_data);

            return *this;
        }

        template <typename T>
        std::shared_ptr<T> ThreadsafeVector<T>::operator[](size_t pos)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_data.empty())
                throw std::exception();

            std::shared_ptr<T> const result = std::make_shared<T>(m_data.at(pos));

            return result;
        }

        template <typename T>
        void ThreadsafeVector<T>::push_back(T _val)
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_data.push_back(std::move(_val));
        }

        size_t ThreadsafeVector<T>::size() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            return m_data.size();
        }
    }
}