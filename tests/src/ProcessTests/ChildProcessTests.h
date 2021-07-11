/*
    Copyright (c) 2016-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_PROCESS_PROCESSTESTS_CHILDPROCESSTESTS_H_
#define _ISHIKO_TEST_PROCESS_PROCESSTESTS_CHILDPROCESSTESTS_H_

#include <Ishiko/Tests/Core.h>

class ChildProcessTests : public Ishiko::Tests::TestSequence
{
public:
    ChildProcessTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void SpawnTest1(Ishiko::Tests::Test& test);
    static void SpawnTest2(Ishiko::Tests::Test& test);
};

#endif
