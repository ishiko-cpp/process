/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "CommandLineSpecificationTests.h"
#include "Ishiko/Process/CommandLineSpecification.h"

using namespace Ishiko::Process;
using namespace Ishiko::Tests;

CommandLineSpecificationTests::CommandLineSpecificationTests(const TestNumber& number,
    const TestEnvironment& environment)
    : TestSequence(number, "CommandLineSpecification tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void CommandLineSpecificationTests::ConstructorTest1(Test& test)
{
    CommandLineSpecification spec;

    ISHTF_PASS();
}
