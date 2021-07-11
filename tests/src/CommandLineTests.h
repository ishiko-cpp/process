/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_COMMANDLINETESTS_H_
#define _ISHIKO_TEST_COMMANDLINETESTS_H_

#include <Ishiko/Tests/Core.h>

class CommandLineTests : public Ishiko::Tests::TestSequence
{
public:
    CommandLineTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
    static void ConstructorTest3(Ishiko::Tests::Test& test);
    static void ConstructorTest4(Ishiko::Tests::Test& test);
    static void ConstructorTest5(Ishiko::Tests::Test& test);
    static void ConstructorTest6(Ishiko::Tests::Test& test);
    static void ConstructorTest7(Ishiko::Tests::Test& test);
    static void ConstructorTest8(Ishiko::Tests::Test& test);
    static void ToStringTest1(Ishiko::Tests::Test& test);
    static void ToStringTest2(Ishiko::Tests::Test& test);
    static void ToStringTest3(Ishiko::Tests::Test& test);
    static void ToStringTest4(Ishiko::Tests::Test& test);
};

#endif
