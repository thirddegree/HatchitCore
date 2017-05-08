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

/**
 * \file ht_threadvector.h
 * \brief ThreadsafeVector class definition
 * \author Matt Guerrette (direct3Dtutorials@gmail.com)
 * \author Third-Degree contributors (https://github.com/thirddegree)
 *
 * This file contains definition for ThreadsafeVector class
 */

#include <ht_platform.h>
#include <vector>
#include <mutex>
#include <memory>
#include <cassert>

namespace Hatchit
{
    namespace Core
    {
        /**
        * \class ThreadsafeVector
        * \brief wrapper for std::vector that provides thread-safe functions
        */
        template <typename T>
        class HT_API ThreadsafeVector
        {
        public:

            /**
            * \brief Creates empty ThreadsafeVector
            ***/
            ThreadsafeVector();

            /**
            * \brief Creates copy of given ThreadsafeVector
            **/
            ThreadsafeVector(const ThreadsafeVector& other);

            /**
            * \brief Moves data from given ThreadsafeVector into new ThreadsafeVector
            **/
            ThreadsafeVector(ThreadsafeVector&& other);

            /**
            * \brief Copies data from one ThreadsafeVector into current ThreadsafeVector
            *
            * Copies data from one ThreadsafeVector into current ThreadsafeVector.
            * One must be cautious when assigning Threadsafe objects to each other,
            * as assignments of one object to itself will cause deadlock, and
            * assignments of objects to each other concurrently may cause
            * deadlock.
            **/
            ThreadsafeVector& operator=(const ThreadsafeVector& other);

            /**
            * \brief Moves data from temporary ThreadsafeVector into current ThreadsafeVector
            *
            * Moves data from temporary ThreadsafeVector into current ThreadsafeVector.
            * One must be cautious when assigning Threadsafe objects to each other,
            * as assignments of one object to itself will cause deadlock, and
            * assignments of objects to each other concurrently may cause
            * deadlock.
            **/
            ThreadsafeVector& operator=(ThreadsafeVector&& other);

            /**
            * \brief Returns a shared ptr copy to the element at specified location
            *
            * No bounds checking is performed.
            **/
            std::shared_ptr<T> operator[](size_t pos);

            /**
            * \brief Adds a new value to ThreadsafeVector
            **/
            void push_back(T _val);

            /**
            * \brief Returns the current number of elements in ThreadsafeVector
            **/
            size_t size() const;

        private:
            std::vector<T>      m_data;
            mutable std::mutex  m_mutex;
        };
    }
}

#include <ht_threadvector.inl>