/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "CommandLineTests.h"
#include "Ishiko/Process/CommandLine.h"

using namespace Ishiko::Tests;

CommandLineTests::CommandLineTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "CommandLine tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
}

void CommandLineTests::ConstructorTest1(Test& test)
{
    Ishiko::Process::CommandLine commandLine("executable");

    ISHTF_FAIL_IF_NEQ(commandLine.executable(), "executable");
    ISHTF_PASS();
}

void CommandLineTests::ConstructorTest2(Test& test)
{
    Ishiko::Process::CommandLine commandLine(std::string("executable"));

    ISHTF_FAIL_IF_NEQ(commandLine.executable(), "executable");
    ISHTF_PASS();
}
