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
#include <ht_singleton.h>
#include <ht_string.h>
#include <ht_timer.h>
#include <map>

namespace Hatchit
{
    namespace Core
    {
        class HT_API Profiler : public Singleton<Profiler>
        {
        public:
            class Sample
            {
            public:
                Sample();
                Sample(const std::string& name, float elapsedTime);

                const std::string& Name() const;
                const uint32_t Count() const;
                const float    ElapsedTime() const;

                void Increment();
                void Decrement();

            private:
                std::string m_name;
                uint32_t    m_count;
                float       m_elapsedTime;
            };

            static void StoreSample(Sample& sample);
            static void Dump();

        private:
            std::map<std::string, Sample> m_samples;
        };


        class HT_API AutoProfile
        {
        public:
            AutoProfile(const std::string& name);

            ~AutoProfile();

        private:
            std::string m_name;
            Timer       m_timer;
        };

    }
}

#ifndef HT_PROFILE
#define HT_PROFILE(name) Hatchit::Core::AutoProfile p(name)
#endif
