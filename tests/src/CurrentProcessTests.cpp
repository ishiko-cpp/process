/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "CurrentProcessTests.h"
#include "Ishiko/Process/CurrentProcess.hpp"
#include <iostream>

using namespace Ishiko;

CurrentProcessTests::CurrentProcessTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "CurrentProcess tests", context)
{
    append<HeapAllocationErrorsTest>("RedirectStandardOutputToFile test 1", RedirectStandardOutputToFileTest1);
    append<HeapAllocationErrorsTest>("RedirectStandardErrorToFile test 1", RedirectStandardErrorToFileTest1);
}

void CurrentProcessTests::RedirectStandardOutputToFileTest1(Test& test)
{
    boost::filesystem::path outputPath = test.context().getOutputPath("RedirectStandardOutputToFileTest1.txt");
    
    CurrentProcess::RedirectStandardOutputToFile(outputPath.string());

    std::cout << "Hello World!" << std::endl;

    CurrentProcess::RedirectStandardOutputToTerminal();

    std::cout << "should not be in the file" << std::endl;

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("RedirectStandardOutputToFileTest1.txt");
    ISHIKO_TEST_PASS();
}

void CurrentProcessTests::RedirectStandardErrorToFileTest1(Test& test)
{
    boost::filesystem::path outputPath = test.context().getOutputPath("RedirectStandardErrorToFileTest1.txt");

    CurrentProcess::RedirectStandardErrorToFile(outputPath.string());

    std::cerr << "Hello World!" << std::endl;

    CurrentProcess::RedirectStandardErrorToTerminal();

    std::cerr << "should not be in the file" << std::endl;

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("RedirectStandardErrorToFileTest1.txt");
    ISHIKO_TEST_PASS();
}
