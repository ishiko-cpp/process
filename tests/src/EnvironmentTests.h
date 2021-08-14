/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_PROCESS_ENVIRONMENTTESTS_H_
#define _ISHIKO_TEST_PROCESS_ENVIRONMENTTESTS_H_

#include <Ishiko/Tests/Core.h>

class EnvironmentTests : public Ishiko::Tests::TestSequence
{
public:
    EnvironmentTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
    static void SetTest1(Ishiko::Tests::Test& test);
    static void SetTest2(Ishiko::Tests::Test& test);
    static void SetTest3(Ishiko::Tests::Test& test);
    static void FindTest1(Ishiko::Tests::Test& test);
    static void ToEnvironmentArrayTest1(Ishiko::Tests::Test& test);
    static void ToEnvironmentArrayTest2(Ishiko::Tests::Test& test);
    static void ToEnvironmentBlockTest1(Ishiko::Tests::FileComparisonTest& test);
    static void ToEnvironmentBlockTest2(Ishiko::Tests::FileComparisonTest& test);
};

#endif
