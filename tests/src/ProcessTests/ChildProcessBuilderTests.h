/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TEST_PROCESS_PROCESSTESTS_CHILDPROCESSBUILDERTESTS_H_
#define _ISHIKO_CPP_TEST_PROCESS_PROCESSTESTS_CHILDPROCESSBUILDERTESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class ChildProcessBuilderTests : public Ishiko::TestSequence
{
public:
    ChildProcessBuilderTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void StartTest1(Ishiko::Test& test);
    static void StartTest2(Ishiko::Test& test);
    static void StartTest3(Ishiko::Test& test);
    static void RedirectStandardOutputToFileTest1(Ishiko::Test& test);
    static void StartTest4(Ishiko::Test& test);
    static void StartTest5(Ishiko::Test& test);
    static void StartTest6(Ishiko::Test& test);
};

#endif
