/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TEST_PROCESS_CURRENTENVIRONMENTTESTS_H_
#define _ISHIKO_CPP_TEST_PROCESS_CURRENTENVIRONMENTTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class CurrentEnvironmentTests : public Ishiko::TestSequence
{
public:
    CurrentEnvironmentTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void SetTest1(Ishiko::Test& test);
    static void SetTest2(Ishiko::Test& test);
    static void FindTest1(Ishiko::Test& test);
    static void ToMapTest1(Ishiko::Test& test);
    static void ExpandVariablesInStringTest1(Ishiko::Test& test);
    static void ExpandVariablesInStringTest2(Ishiko::Test& test);
    static void ExpandVariablesInStringTest3(Ishiko::Test& test);
    static void ExpandVariablesInStringTest4(Ishiko::Test& test);
    static void ExpandVariablesInStringTest5(Ishiko::Test& test);
    static void ExpandVariablesInStringTest6(Ishiko::Test& test);
};

#endif
