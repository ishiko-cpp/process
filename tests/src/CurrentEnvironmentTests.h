/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_PROCESS_CURRENTENVIRONMENTTESTS_H_
#define _ISHIKO_TEST_PROCESS_CURRENTENVIRONMENTTESTS_H_

#include <Ishiko/Tests/Core.h>

class CurrentEnvironmentTests : public Ishiko::Tests::TestSequence
{
public:
    CurrentEnvironmentTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void SetTest1(Ishiko::Tests::Test& test);
    static void SetTest2(Ishiko::Tests::Test& test);
    static void FindTest1(Ishiko::Tests::Test& test);
    static void ToMapTest1(Ishiko::Tests::Test& test);
    static void ExpandVariablesInStringTest1(Ishiko::Tests::Test& test);
    static void ExpandVariablesInStringTest2(Ishiko::Tests::Test& test);
    static void ExpandVariablesInStringTest3(Ishiko::Tests::Test& test);
    static void ExpandVariablesInStringTest4(Ishiko::Tests::Test& test);
    static void ExpandVariablesInStringTest5(Ishiko::Tests::Test& test);
    static void ExpandVariablesInStringTest6(Ishiko::Tests::Test& test);
};

#endif
