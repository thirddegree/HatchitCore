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
#include <vector>
#include <mutex>
#include <memory>

namespace Hatchit
{
    namespace Core
    {
        /**
        \class ThreadsafeVector<T>
        \ingroup HatchitCore
        \brief wrapper for std::vector that provides thread-safe functions
        */
        template <typename T>
        class HT_API ThreadsafeVector
        {
        public:
            ThreadsafeVector();
            ThreadsafeVector(const ThreadsafeVector& other);
            ThreadsafeVector(ThreadsafeVector&& other);

            ThreadsafeVector& operator=(const ThreadsafeVector&);
            ThreadsafeVector& operator=(ThreadsafeVector&&);

            std::shared_ptr<T> operator[](size_t pos);

            void push_back(T _val);

            size_t size() const;

        private:
            std::vector<T>      m_data;
            mutable std::mutex  m_mutex;
        };
    }
}

#include <ht_threadvector.inl>