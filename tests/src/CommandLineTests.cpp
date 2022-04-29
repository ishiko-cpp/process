/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "CommandLineTests.h"
#include "Ishiko/Process/CommandLine.h"

using namespace Ishiko;

CommandLineTests::CommandLineTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "CommandLine tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("Constructor test 3", ConstructorTest3);
    append<HeapAllocationErrorsTest>("Constructor test 4", ConstructorTest4);
    append<HeapAllocationErrorsTest>("Constructor test 5", ConstructorTest5);
    append<HeapAllocationErrorsTest>("Constructor test 6", ConstructorTest6);
    append<HeapAllocationErrorsTest>("Constructor test 7", ConstructorTest7);
    append<HeapAllocationErrorsTest>("Constructor test 8", ConstructorTest8);
    append<HeapAllocationErrorsTest>("toString test 1", ToStringTest1);
    append<HeapAllocationErrorsTest>("toString test 2", ToStringTest2);
    append<HeapAllocationErrorsTest>("toString test 3", ToStringTest3);
    append<HeapAllocationErrorsTest>("toString test 4", ToStringTest4);
}

void CommandLineTests::ConstructorTest1(Test& test)
{
    CommandLine commandLine("executable");

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eRaw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eQuoteIfNeeded), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::eRaw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::eQuoteIfNeeded);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 0);
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest2(Test& test)
{
    CommandLine commandLine(std::string("executable"));

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eRaw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eQuoteIfNeeded), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::eRaw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::eQuoteIfNeeded);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 0);
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest3(Test& test)
{
    CommandLine commandLine("executable arg1");

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eRaw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eQuoteIfNeeded), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::eRaw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::eQuoteIfNeeded);

    ISHIKO_TEST_ABORT_IF_NEQ(raw_arguments.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments[0], "arg1");
    ISHIKO_TEST_ABORT_IF_NEQ(quoted_if_needed_arguments.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments[0], "arg1");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest4(Test& test)
{
    boost::filesystem::path executable = "relative/path/executable";
    CommandLine commandLine(executable, {});

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eRaw), "relative/path/executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eQuoteIfNeeded), "relative/path/executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::eRaw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::eQuoteIfNeeded);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 0);
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest5(Test& test)
{
    boost::filesystem::path executable = "relative\\path\\executable";
    CommandLine commandLine(executable, {});

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eRaw), "relative\\path\\executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eQuoteIfNeeded), "relative\\path\\executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::eRaw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::eQuoteIfNeeded);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 0);
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest6(Test& test)
{
    CommandLine commandLine("executable", {"arg1"});

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eRaw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eQuoteIfNeeded), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::eRaw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::eQuoteIfNeeded);

    ISHIKO_TEST_ABORT_IF_NEQ(raw_arguments.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments[0], "arg1");
    ISHIKO_TEST_ABORT_IF_NEQ(quoted_if_needed_arguments.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments[0], "arg1");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest7(Test& test)
{
    CommandLine commandLine("executable", { "arg1", "arg2" });

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eRaw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eQuoteIfNeeded), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::eRaw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::eQuoteIfNeeded);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments[0], "arg1");
    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments[1], "arg2");
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments[0], "arg1");
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments[1], "arg2");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest8(Test& test)
{
    CommandLine commandLine("executable", { "arg 1" });

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eRaw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::eQuoteIfNeeded), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::eRaw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::eQuoteIfNeeded);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments[0], "arg 1");
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments[0], "\"arg 1\"");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ToStringTest1(Test& test)
{
    CommandLine commandLine("executable");

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::eRaw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::eQuoteIfNeeded), "executable");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ToStringTest2(Test& test)
{
    CommandLine commandLine("executable arg1");

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::eRaw), "executable arg1");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::eQuoteIfNeeded), "executable arg1");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ToStringTest3(Test& test)
{
    CommandLine commandLine("executable", {"arg1"});

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::eRaw), "executable arg1");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::eQuoteIfNeeded), "executable arg1");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ToStringTest4(Test& test)
{
    CommandLine commandLine("executable with spaces", { "arg 1" });

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::eRaw), "executable with spaces arg 1");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::eQuoteIfNeeded), "\"executable with spaces\" \"arg 1\"");
    ISHIKO_TEST_PASS();
}
