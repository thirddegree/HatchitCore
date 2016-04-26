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
#include <ht_file.h>
#include <ht_inisettings.h>
#include <ht_debug.h>
#include <ht_os.h>


using namespace Hatchit;
using namespace Hatchit::Core;


TEST(INITest, Serialize)
{
    File file;

    try
    {

        file.Open(os_exec_dir() + "test.ini", File::FileMode::WriteBinary);
        INISettings s;
        s.SetValue("TEST", "iVal", 600);
        s.SetValue("TEST", "bVal", true);
        s.SetValue("TEST", "fVal", 2.5f);
        s.SetValue("TEST", "dVal", 35.5);

        s.Write(&file);

        file.Close();


        file.Open(os_exec_dir() + "test.ini", File::FileMode::ReadText);

        INISettings r;
        r.Load(&file);

        bool    bValue = r.GetValue("TEST", "bVal", false);
        int     iValue = r.GetValue("TEST", "iVal", 0);
        float   fValue = r.GetValue("TEST", "fVal", 0.0f);
        double  dValue = r.GetValue("TEST", "dVal", 0.0);

        EXPECT_EQ(600, iValue);
        EXPECT_EQ(true, bValue);
        EXPECT_EQ(2.5f, fValue);
        EXPECT_EQ(35.5, dValue);
    }
    catch(std::exception& e)
    {
        HT_DEBUG_PRINTF("%s\n", e.what());
        FAIL();
    }
}
