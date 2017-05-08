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
#include <ht_types.h>
#include <map>
#include <stack>
#include <vector>

namespace Hatchit
{
    namespace Core
    {
        /**
         * \class Profiler
         * \brief Defines a Runtime Profiler Singleton
         *
         * This runtime profiler singleton manages all runtime
         * profiling samples and managers the distributiion
         * and hierarchy of the samples
         *
         * NOTE:
         *      The current implementation does not support distributed
         *      hierarchical sampling.
         */
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

                void SetName(const std::string& name);
                void SetCount(uint32_t count);
                void SetElapsedTime(float elapsed);
                void Increment();
                void Decrement();

                void AddChild(Sample& child);

                const std::vector<Sample>& Children();

            private:
                std::string m_name;
                uint32_t    m_count;
                float       m_elapsedTime;

                std::vector<Sample> m_children;
            };

            static void PushSample(Sample* sample);
            static void PopSample();
            static void Dump();

        private:
            //std::map<std::string, Sample> m_samples;
            std::vector<Sample> m_samples;
            std::stack<Sample*> m_sampleStack;
        };


        /**
         * \class AutoProfile
         * \brief Simple auto-profiling class
         *
         * This class creates a timed sample of code execution
         * automatically upon leaving scope and being destroyed.
         * All code executed between creation and destruction of this
         * object will be timed and a sample will be added to the master list.
         *
         * NOTE:
         *      Direct creation of this object type is not recommended. Instead, please
         *      use the provided macro HT_PROFILE
         */
        class HT_API AutoProfile
        {
        public:
            AutoProfile(const std::string& name);

            ~AutoProfile();

        private:
            std::string           m_name;
            Timer                 m_timer;
            Profiler::Sample*     m_sample;
        };

    }
}

#ifndef HT_PROFILE
#define HT_PROFILE(name) Hatchit::Core::AutoProfile p(name)
#endif
