/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TEST_CURRENTPROCESSTESTS_H_
#define _ISHIKO_CPP_TEST_CURRENTPROCESSTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class CurrentProcessTests : public Ishiko::TestSequence
{
public:
    CurrentProcessTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void RedirectStandardOutputToFileTest1(Ishiko::FileComparisonTest& test);
};

#endif
