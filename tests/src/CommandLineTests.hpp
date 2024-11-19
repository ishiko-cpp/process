// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_PROCESS_TESTS_COMMANDLINETESTS_HPP
#define GUARD_ISHIKO_CPP_PROCESS_TESTS_COMMANDLINETESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

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
