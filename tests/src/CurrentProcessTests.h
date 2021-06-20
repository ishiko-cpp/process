/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_CURRENTPROCESSTESTS_H_
#define _ISHIKO_TEST_CURRENTPROCESSTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class CurrentProcessTests : public Ishiko::Tests::TestSequence
{
public:
    CurrentProcessTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void RedirectStandardOutputToFileTest1(Ishiko::Tests::FileComparisonTest& test);
};

#endif
