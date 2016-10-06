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
        void Profiler::PushSample(Profiler::Sample *sample)
        {
            Profiler& _instance = Profiler::instance();
            
            _instance.m_sampleStack.push(sample);
        }

        void Profiler::PopSample()
        {
            /**
             * Now we need to pop the active sample
             * off of the stack. In doing so, if there is a parent
             * sample we must add the popped sample to that parents children list
             */

            Profiler& _instance = Profiler::instance();

            Profiler::Sample* current = _instance.m_sampleStack.top();
            _instance.m_sampleStack.pop(); ///remove from samples stack

            if(!_instance.m_sampleStack.empty())
            {
                Profiler::Sample *parent = _instance.m_sampleStack.top();
                parent->AddChild(*current); ///add a copy of the sample information as child
            }
            else
            {
                /**
                * If this was the last sample in the stack (i.e topmost)
                * we must add it to the official sample list
                */
                _instance.m_samples.push_back(*current);
            }
        }

        void Profiler::Dump()
        {
            Profiler& _instance = Profiler::instance();

            HT_DEBUG_PRINTF("-----PROFILING------\n");
            for (auto& sample : _instance.m_samples)
            {
                HT_DEBUG_PRINTF("Sample: \t%s \tElapsed: \t%.9f sec\n", sample.Name(), sample.ElapsedTime());
                if(!sample.Children().empty())
                {
                    HT_DEBUG_PRINTF("\tChildren:\n");
                    for(auto& child : sample.Children())
                    {
                        HT_DEBUG_PRINTF("\t\tSample: \t%s \tElapsed: \t%.9f sec\n", child.Name(), child.ElapsedTime());
                    }
                }

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

        const std::vector<Profiler::Sample>& Profiler::Sample::Children()
        {
            return m_children;
        }

        void Profiler::Sample::SetName(const std::string &name)
        {
            m_name = name;
        }

        void Profiler::Sample::SetCount(uint32_t count)
        {
            m_count = count;
        }

        void Profiler::Sample::SetElapsedTime(float elapsed)
        {
            m_elapsedTime = elapsed;
        }

        void Profiler::Sample::Increment()
        {
            m_count++;
        }

        void Profiler::Sample::Decrement()
        {
            m_count--;
        }

        void Profiler::Sample::AddChild(Sample &child)
        {
            m_children.push_back(child);
        }

        AutoProfile::AutoProfile(const std::string& name)
        {
            m_name = name;
            m_timer.Start();
            m_sample = new Profiler::Sample(name, 0.0f);

            Profiler::PushSample(m_sample);
        }

        AutoProfile::~AutoProfile()
        {
            m_timer.Stop();

            float elapsed = m_timer.ElapsedTime();
            m_sample->SetElapsedTime(elapsed);

            Profiler::PopSample();

            delete m_sample;
        }
    }
}