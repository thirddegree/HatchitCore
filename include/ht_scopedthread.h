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

#include <ht_platform.h> //HT_API
#include <ht_noncopy.h> //INonCopy
#include <thread> //std::thread

namespace Hatchit
{   
    namespace Core
    {   
        /**
        \class ScopedThread
        \ingroup HatchitCore
        \brief A safety wrapper for std::threads to safely join threads
        **/
        class HT_API ScopedThread : public INonCopy
        {
        public:
            explicit ScopedThread(std::thread _t);
            virtual ~ScopedThread();       
        
        private:
            std::thread t;            
        };
    }
}
