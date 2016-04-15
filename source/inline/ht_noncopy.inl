#pragma once

#include <ht_noncopy.h>

namespace Hatchit
{
    namespace Core
    {
        INonCopy::INonCopy() = default;

        INonCopy::~INonCopy() = default;

        INonCopy::INonCopy(INonCopy&&) = default;

        INonCopy& INonCopy::operator=(INonCopy&&) = default;
    }
}