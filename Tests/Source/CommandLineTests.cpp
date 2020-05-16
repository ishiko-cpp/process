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
    append<HeapAllocationErrorsTest>("Constructor test 3", ConstructorTest3);
    append<HeapAllocationErrorsTest>("Constructor test 4", ConstructorTest4);
    append<HeapAllocationErrorsTest>("Constructor test 5", ConstructorTest5);
    append<HeapAllocationErrorsTest>("toString test 1", ToStringTest1);
    append<HeapAllocationErrorsTest>("toString test 2", ToStringTest2);
}

void CommandLineTests::ConstructorTest1(Test& test)
{
    Ishiko::Process::CommandLine commandLine("executable");

    ISHTF_FAIL_IF_NEQ(commandLine.executable(), "executable");
    ISHTF_FAIL_IF_NEQ(commandLine.arguments().size(), 0);
    ISHTF_PASS();
}

void CommandLineTests::ConstructorTest2(Test& test)
{
    Ishiko::Process::CommandLine commandLine(std::string("executable"));

    ISHTF_FAIL_IF_NEQ(commandLine.executable(), "executable");
    ISHTF_FAIL_IF_NEQ(commandLine.arguments().size(), 0);
    ISHTF_PASS();
}

void CommandLineTests::ConstructorTest3(Test& test)
{
    Ishiko::Process::CommandLine commandLine("executable with spaces");

    ISHTF_FAIL_IF_NEQ(commandLine.executable(), "\"executable with spaces\"");
    ISHTF_FAIL_IF_NEQ(commandLine.arguments().size(), 0);
    ISHTF_PASS();
}

void CommandLineTests::ConstructorTest4(Test& test)
{
    boost::filesystem::path executable = "relative/path/executable";
    Ishiko::Process::CommandLine commandLine(executable);

    ISHTF_FAIL_IF_NEQ(commandLine.executable(), "relative/path/executable");
    ISHTF_FAIL_IF_NEQ(commandLine.arguments().size(), 0);
    ISHTF_PASS();
}

void CommandLineTests::ConstructorTest5(Test& test)
{
    boost::filesystem::path executable = "relative\\path\\executable";
    Ishiko::Process::CommandLine commandLine(executable);

    ISHTF_FAIL_IF_NEQ(commandLine.executable(), "relative\\path\\executable");
    ISHTF_FAIL_IF_NEQ(commandLine.arguments().size(), 0);
    ISHTF_PASS();
}

void CommandLineTests::ToStringTest1(Test& test)
{
    Ishiko::Process::CommandLine commandLine("executable");

    ISHTF_FAIL_IF_NEQ(commandLine.toString(), "executable");
    ISHTF_PASS();
}

void CommandLineTests::ToStringTest2(Test& test)
{
    Ishiko::Process::CommandLine commandLine("executable with spaces");

    ISHTF_FAIL_IF_NEQ(commandLine.toString(), "\"executable with spaces\"");
    ISHTF_PASS();
}
