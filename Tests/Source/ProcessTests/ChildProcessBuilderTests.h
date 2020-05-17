/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_PROCESS_PROCESSTESTS_CHILDPROCESSBUILDERTESTS_H_
#define _ISHIKO_TEST_PROCESS_PROCESSTESTS_CHILDPROCESSBUILDERTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class ChildProcessBuilderTests : public Ishiko::Tests::TestSequence
{
public:
    ChildProcessBuilderTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void StartTest1(Ishiko::Tests::Test& test);
    static void StartTest2(Ishiko::Tests::Test& test);
    static void RedirectStandardOutputToFileTest1(Ishiko::Tests::FileComparisonTest& test);
    static void StartTest3(Ishiko::Tests::FileComparisonTest& test);
    static void StartProcessTest1(Ishiko::Tests::Test& test);
};

#endif
