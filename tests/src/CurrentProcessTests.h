/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TEST_CURRENTPROCESSTESTS_H_
#define _ISHIKO_CPP_TEST_CURRENTPROCESSTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class CurrentProcessTests : public Ishiko::Tests::TestSequence
{
public:
    CurrentProcessTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void RedirectStandardOutputToFileTest1(Ishiko::Tests::FileComparisonTest& test);
};

#endif
