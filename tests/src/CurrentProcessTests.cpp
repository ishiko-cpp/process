/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "CurrentProcessTests.h"
#include "Ishiko/Process/CurrentProcess.h"
#include <boost/filesystem/operations.hpp>
#include <iostream>

using namespace Ishiko;
using namespace Ishiko::Process;

CurrentProcessTests::CurrentProcessTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "CurrentProcess tests", context)
{
    append<FileComparisonTest>("RedirectStandardOutputToFile test 1", RedirectStandardOutputToFileTest1);
}

void CurrentProcessTests::RedirectStandardOutputToFileTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.context().getTestOutputPath("RedirectStandardOutputToFileTest1.txt"));
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataPath("RedirectStandardOutputToFileTest1.txt"));

    CurrentProcess::RedirectStandardOutputToFile(outputPath.string());

    std::cout << "Hello World!" << std::endl;

    CurrentProcess::RedirectStandardOutputToTerminal();

    std::cout << "should not be in the file" << std::endl;

    ISHIKO_TEST_PASS();
}
