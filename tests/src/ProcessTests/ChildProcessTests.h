/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TEST_PROCESS_PROCESSTESTS_CHILDPROCESSTESTS_H_
#define _ISHIKO_CPP_TEST_PROCESS_PROCESSTESTS_CHILDPROCESSTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class ChildProcessTests : public Ishiko::TestSequence
{
public:
    ChildProcessTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void SpawnTest1(Ishiko::Test& test);
    static void SpawnTest2(Ishiko::Test& test);
};

#endif
