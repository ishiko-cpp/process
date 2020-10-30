/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_TESTS_UTILITIESTESTS_H_
#define _ISHIKO_PROCESS_TESTS_UTILITIESTESTS_H_

#include <Ishiko/TestFramework/TestFrameworkCore.h>

class UtilitiesTests : public Ishiko::Tests::TestSequence
{
public:
    UtilitiesTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);
};

#endif
