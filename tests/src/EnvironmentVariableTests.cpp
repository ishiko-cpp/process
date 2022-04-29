/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "EnvironmentVariableTests.h"

using namespace Ishiko;

EnvironmentVariableTests::EnvironmentVariableTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "EnvironmentVariable tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void EnvironmentVariableTests::ConstructorTest1(Test& test)
{
    EnvironmentVariable variable("name=value");

    ISHIKO_TEST_FAIL_IF_NEQ(variable.name(), "name");
    ISHIKO_TEST_FAIL_IF_NEQ(variable.value(), "value");
    ISHIKO_TEST_PASS();
}
