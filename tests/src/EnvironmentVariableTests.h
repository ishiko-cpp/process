/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TEST_PROCESS_ENVIRONMENTVARIABLETESTS_H_
#define _ISHIKO_CPP_TEST_PROCESS_ENVIRONMENTVARIABLETESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class EnvironmentVariableTests : public Ishiko::TestSequence
{
public:
    EnvironmentVariableTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
