// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

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

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::raw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::quote_if_needed), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::Mode::raw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::Mode::quote_if_needed);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 0);
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest2(Test& test)
{
    CommandLine commandLine(std::string("executable"));

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::raw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::quote_if_needed), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::Mode::raw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::Mode::quote_if_needed);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 0);
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest3(Test& test)
{
    CommandLine commandLine("executable arg1");

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::raw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::quote_if_needed), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::Mode::raw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::Mode::quote_if_needed);

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

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::raw), "relative/path/executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::quote_if_needed), "relative/path/executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::Mode::raw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::Mode::quote_if_needed);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 0);
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest5(Test& test)
{
    boost::filesystem::path executable = "relative\\path\\executable";
    CommandLine commandLine(executable, {});

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::raw), "relative\\path\\executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::quote_if_needed),
        "relative\\path\\executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::Mode::raw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::Mode::quote_if_needed);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 0);
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest6(Test& test)
{
    CommandLine commandLine("executable", {"arg1"});

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::raw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::quote_if_needed), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::Mode::raw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::Mode::quote_if_needed);

    ISHIKO_TEST_ABORT_IF_NEQ(raw_arguments.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments[0], "arg1");
    ISHIKO_TEST_ABORT_IF_NEQ(quoted_if_needed_arguments.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments[0], "arg1");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ConstructorTest7(Test& test)
{
    CommandLine commandLine("executable", { "arg1", "arg2" });

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::raw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::quote_if_needed), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::Mode::raw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::Mode::quote_if_needed);

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

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::raw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.getExecutable(CommandLine::Mode::quote_if_needed), "executable");

    std::vector<std::string> raw_arguments = commandLine.getArguments(CommandLine::Mode::raw);
    std::vector<std::string> quoted_if_needed_arguments = commandLine.getArguments(CommandLine::Mode::quote_if_needed);

    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(raw_arguments[0], "arg 1");
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(quoted_if_needed_arguments[0], "\"arg 1\"");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ToStringTest1(Test& test)
{
    CommandLine commandLine("executable");

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::Mode::raw), "executable");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::Mode::quote_if_needed), "executable");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ToStringTest2(Test& test)
{
    CommandLine commandLine("executable arg1");

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::Mode::raw), "executable arg1");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::Mode::quote_if_needed), "executable arg1");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ToStringTest3(Test& test)
{
    CommandLine commandLine("executable", {"arg1"});

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::Mode::raw), "executable arg1");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::Mode::quote_if_needed), "executable arg1");
    ISHIKO_TEST_PASS();
}

void CommandLineTests::ToStringTest4(Test& test)
{
    CommandLine commandLine("executable with spaces", { "arg 1" });

    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::Mode::raw), "executable with spaces arg 1");
    ISHIKO_TEST_FAIL_IF_NEQ(commandLine.toString(CommandLine::Mode::quote_if_needed),
        "\"executable with spaces\" \"arg 1\"");
    ISHIKO_TEST_PASS();
}
