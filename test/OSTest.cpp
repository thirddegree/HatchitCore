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

#include <gtest/gtest.h>
#include <ht_os.h>

using namespace Hatchit;
using namespace Hatchit::Core;

TEST(OS, mkdir)
{
    /*test mkdir command*/
    os_mkdir("testdir");

    EXPECT_EQ(true, os_isdir("testdir"));
}
