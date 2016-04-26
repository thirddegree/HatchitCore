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
#include <ht_jsonhelper.h>

using namespace Hatchit;
using namespace Hatchit::Core;

static const JSON TestJson = R"(
    {
        "message": "Hello, world!",
        "meaning_of_life": 42,
        "pi": 3.1415926535897932384626433832795,
        "is_civil_war_out_yet": false,
        "my_guid": "{cbe9644b-bd06-4391-9e9a-57913180254f}"
    }
)"_json;

// Ensure that these match the values in the JSON above!
static const std::string TestString = "Hello, world!";
static const int64_t     TestInt    = 42;
static const double      TestDouble = 3.1415926535897932384626433832795;
static const bool        TestBool   = false;
static       Guid        TestGuid;

TEST(JsonTest, Extraction)
{
    ASSERT_TRUE(Guid::Parse("{cbe9644b-bd06-4391-9e9a-57913180254f}", TestGuid));

    std::string jsonString;
    int64_t jsonInt;
    double jsonDouble;
    bool jsonBool;
    Guid jsonGuid;

#if defined(_DEBUG) || defined(DEBUG)
    ASSERT_TRUE(JsonExtract(TestJson, "message", jsonString));
    ASSERT_TRUE(JsonExtract(TestJson, "meaning_of_life", jsonInt));
    ASSERT_TRUE(JsonExtract(TestJson, "pi", jsonDouble));
    ASSERT_TRUE(JsonExtract(TestJson, "is_civil_war_out_yet", jsonBool));
    ASSERT_TRUE(JsonExtract(TestJson, "my_guid", jsonGuid));
#else
    try
    {
        JsonExtract(TestJson, "message", jsonString);
        JsonExtract(TestJson, "meaning_of_life", jsonInt);
        JsonExtract(TestJson, "pi", jsonDouble);
        JsonExtract(TestJson, "is_civil_war_out_yet", jsonBool);
        JsonExtract(TestJson, "my_guid", jsonGuid);
    }
    catch (...)
    {
        FAIL() << "Extractions failed!";
    }
#endif

    EXPECT_EQ(TestString, jsonString);
    EXPECT_EQ(TestInt, jsonInt);
    EXPECT_EQ(TestDouble, jsonDouble);
    EXPECT_EQ(TestBool, jsonBool);
    EXPECT_EQ(TestGuid, jsonGuid);
}
