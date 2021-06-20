/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "CurrentProcessTests.h"
#include "Ishiko/Process/CurrentProcess.h"
#include <boost/filesystem/operations.hpp>
#include <iostream>

using namespace Ishiko::Tests;

CurrentProcessTests::CurrentProcessTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "CurrentProcess tests", environment)
{
    append<FileComparisonTest>("RedirectStandardOutputToFile test 1", RedirectStandardOutputToFileTest1);
}

void CurrentProcessTests::RedirectStandardOutputToFileTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "RedirectStandardOutputToFileTest1.txt");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "RedirectStandardOutputToFileTest1.txt");

    Ishiko::Process::CurrentProcess::RedirectStandardOutputToFile(outputPath.string());

    std::cout << "Hello World!" << std::endl;

    Ishiko::Process::CurrentProcess::RedirectStandardOutputToTerminal();

    std::cout << "should not be in the file" << std::endl;

    ISHTF_PASS();
}
