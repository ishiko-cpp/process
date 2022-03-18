/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TEST_COMMANDLINETESTS_H_
#define _ISHIKO_CPP_TEST_COMMANDLINETESTS_H_

#include <Ishiko/Tests/Core.hpp>

class CommandLineTests : public Ishiko::TestSequence
{
public:
    CommandLineTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void ConstructorTest3(Ishiko::Test& test);
    static void ConstructorTest4(Ishiko::Test& test);
    static void ConstructorTest5(Ishiko::Test& test);
    static void ConstructorTest6(Ishiko::Test& test);
    static void ConstructorTest7(Ishiko::Test& test);
    static void ConstructorTest8(Ishiko::Test& test);
    static void ToStringTest1(Ishiko::Test& test);
    static void ToStringTest2(Ishiko::Test& test);
    static void ToStringTest3(Ishiko::Test& test);
    static void ToStringTest4(Ishiko::Test& test);
};

#endif
