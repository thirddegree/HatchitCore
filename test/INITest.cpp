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
#include <ht_inireader.h>
#include <ht_iniwriter.h>
#include <ht_debug.h>
#include <ht_os.h>


using namespace Hatchit;
using namespace Hatchit::Core;


TEST(INITest, Serialize)
{
    File file;

    try
    {

        file.Open(os_exec_dir() + "test.ini", FileMode::WriteBinary);
        INIWriter writer;
        writer.SetValue("TEST", "iVal", 600);
        writer.SetValue("TEST", "bVal", true);
        writer.SetValue("TEST", "fVal", 2.5f);
        writer.SetValue("TEST", "dVal", 35.5);

        writer.Write(&file);

        file.Close();


        file.Open(os_exec_dir() + "test.ini", FileMode::ReadText);

        INIReader reader;
        reader.Load(&file);

        bool    bValue = reader.GetValue("TEST", "bVal", false);
        int     iValue = reader.GetValue("TEST", "iVal", 0);
        float   fValue = reader.GetValue("TEST", "fVal", 0.0f);
        double  dValue = reader.GetValue("TEST", "dVal", 0.0);

        EXPECT_EQ(600, iValue);
        EXPECT_EQ(true, bValue);
        EXPECT_EQ(2.5f, fValue);
        EXPECT_EQ(35.5, dValue);
    }
    catch(std::exception& e)
    {
        DebugPrintF("%s\n", e.what());
        FAIL();
    }
}
