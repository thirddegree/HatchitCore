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
        s.SetValue<int>("TEST", "iVal", 600);
        s.SetValue<bool>("TEST", "bVal", true);
        s.SetValue<float>("TEST", "fVal", 2.5f);
        s.SetValue<double>("TEST", "dVal", 35.5);

        s.Write(file);

        file.Close();

        file.Open(os_exec_dir() + "test.ini", File::FileMode::ReadText);

        INISettings r;
        r.Load(file);

        bool    bValue = r.GetValue<bool>("TEST", "bVal");
        int     iValue = r.GetValue<int>("TEST", "iVal");
        float   fValue = r.GetValue<float>("TEST", "fVal");
        double  dValue = r.GetValue<double>("TEST", "dVal");

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
