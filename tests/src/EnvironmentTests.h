// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef _ISHIKO_CPP_TEST_PROCESS_ENVIRONMENTTESTS_H_
#define _ISHIKO_CPP_TEST_PROCESS_ENVIRONMENTTESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class EnvironmentTests : public Ishiko::TestSequence
{
public:
    EnvironmentTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void SetTest1(Ishiko::Test& test);
    static void SetTest2(Ishiko::Test& test);
    static void SetTest3(Ishiko::Test& test);
    static void FindTest1(Ishiko::Test& test);
    static void ToEnvironmentArrayTest1(Ishiko::Test& test);
    static void ToEnvironmentArrayTest2(Ishiko::Test& test);
    static void ToEnvironmentBlockTest1(Ishiko::Test& test);
    static void ToEnvironmentBlockTest2(Ishiko::Test& test);
};

#endif
