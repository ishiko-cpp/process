/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "EnvironmentVariableTests.h"

using namespace Ishiko::Tests;

EnvironmentVariableTests::EnvironmentVariableTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "EnvironmentVariable tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void EnvironmentVariableTests::ConstructorTest1(Test& test)
{
    Ishiko::Process::EnvironmentVariable variable("name=value");

    ISHTF_PASS();
}
