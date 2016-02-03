/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
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
#include <stack>
#include <mutex>
#include <memory>

namespace Hatchit {

    namespace Core {
        
        template <typename T>
        class HT_API threadsafe_stack
        {
        public:
            threadsafe_stack() { }
            threadsafe_stack(const threadsafe_stack& other)
            {
                std::lock_guard<std::mutex> lock(other.m);

                m_data = other.data;
            }
            threadsafe_stack& operator=(const threadsafe_stack&)=delete;

            void push(T _val)
            {
                std::lock_guard<std::mutex> lock(m_mutex);

                m_data.push(_val);
            }

            std::shared_ptr<T> pop()
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                if(m_data.empty())
                    throw std::exception();

                std::shared_ptr<T> const result = std::make_shared<T>(m_data.top());
                m_data.pop();

                return result;        
            }

            void pop(T& _val)
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                if(m_data.empty())
                    throw std::exception();

                _val = m_data.top();
                m_data.pop();
            }
            
            bool empty() const
            {
                std::lock_guard<std::mutex> lock(m_mutex);

                return m_data.empty();
            }
        private:
            std::stack<T>       m_data;
            mutable std::mutex  m_mutex;          
        };
    }
}
