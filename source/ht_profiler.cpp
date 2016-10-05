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

#include <ht_profiler.h>
#include <ht_debug.h>

namespace Hatchit
{
    namespace Core
    {
        void Profiler::StoreSample(Profiler::Sample& sample)
        {
            Profiler& _instance = Profiler::instance();

            std::string name = sample.Name();

            auto it = _instance.m_samples.find(name);
            if (it != _instance.m_samples.end())
            {
                _instance.m_samples[name].Increment();
            }
            else
                _instance.m_samples[name] = sample;
        }

        void Profiler::Dump()
        {
            Profiler& _instance = Profiler::instance();

            HT_DEBUG_PRINTF("-----PROFILING------\n");
            for (auto sample : _instance.m_samples)
            {
                Profiler::Sample s = sample.second;
                HT_DEBUG_PRINTF("Sample: \t%s \tElapsed: \t%.9f sec\n", s.Name(), s.ElapsedTime());
            }
        }

        Profiler::Sample::Sample()
        {
            m_name = "";
            m_count = 1;
            m_elapsedTime = 0.0f;
        }

        Profiler::Sample::Sample(const std::string& name, float elapsedTime)
        {
            m_name = name;
            m_count = 1;
            m_elapsedTime = elapsedTime;
        }

        const std::string& Profiler::Sample::Name() const
        {
            return m_name;
        }

        const uint32_t Profiler::Sample::Count() const
        {
            return m_count;
        }

        const float Profiler::Sample::ElapsedTime() const
        {
            return m_elapsedTime;
        }

        void Profiler::Sample::Increment()
        {
            m_count++;
        }

        void Profiler::Sample::Decrement()
        {
            m_count--;
        }

        AutoProfile::AutoProfile(const std::string& name)
        {
            m_name = name;
            m_timer.Start();
        }

        AutoProfile::~AutoProfile()
        {
            m_timer.Stop();

            float elapsed = m_timer.ElapsedTime();

            Profiler::Sample sample(m_name, elapsed);
            Profiler::StoreSample(sample);
        }
    }
}