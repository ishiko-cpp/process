/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "CommandLineParserTests.h"
#include "Ishiko/Process/CommandLineParser.h"

using namespace Ishiko::Process;
using namespace Ishiko::Tests;

CommandLineParserTests::CommandLineParserTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "CommandLineParser tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void CommandLineParserTests::ConstructorTest1(Test& test)
{
    CommandLineParser parser;

    ISHTF_PASS();
}
