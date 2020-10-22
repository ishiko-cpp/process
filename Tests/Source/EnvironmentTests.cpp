/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "EnvironmentTests.h"
#include "Ishiko/Process/Environment.h"

using namespace Ishiko::Tests;

EnvironmentTests::EnvironmentTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Environment tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void EnvironmentTests::ConstructorTest1(Test& test)
{
    Ishiko::Process::Environment env;

    ISHTF_PASS();
}
