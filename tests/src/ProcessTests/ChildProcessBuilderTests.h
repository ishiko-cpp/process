/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TEST_PROCESS_PROCESSTESTS_CHILDPROCESSBUILDERTESTS_H_
#define _ISHIKO_CPP_TEST_PROCESS_PROCESSTESTS_CHILDPROCESSBUILDERTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class ChildProcessBuilderTests : public Ishiko::Tests::TestSequence
{
public:
    ChildProcessBuilderTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void StartTest1(Ishiko::Tests::Test& test);
    static void StartTest2(Ishiko::Tests::Test& test);
    static void StartTest3(Ishiko::Tests::Test& test);
    static void RedirectStandardOutputToFileTest1(Ishiko::Tests::FileComparisonTest& test);
    static void StartTest4(Ishiko::Tests::FileComparisonTest& test);
    static void StartTest5(Ishiko::Tests::FileComparisonTest& test);
    static void StartTest6(Ishiko::Tests::FileComparisonTest& test);
};

#endif
