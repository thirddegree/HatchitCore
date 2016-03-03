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
#include <ht_platform.h>
#include <ht_debug.h>

using namespace Hatchit;
using namespace Hatchit::Core;

TEST(FormatTest, MemoryPrint)
{
    const char* abra = "abra";
    std::string cad = "cad";
    int         number = 42;
    const char* emoji = "B)";

    std::string formatted = DebugSprintF("%s%s%s %i %s", abra, cad, abra, number, emoji);

    EXPECT_STREQ("abracadabra 42 B)", formatted.c_str());
}

TEST(FormatTest, ConsolePrint)
{
    float num1 = 3.14f;
    float num2 = 4.13f;

    DebugPrintF("%.2f * %.2f = %.4f\n", num1, num2, num1 * num2);
}
