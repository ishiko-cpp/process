/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ChildProcessBuilderTests.h"
#include "Ishiko/Process/ChildProcessBuilder.h"
#include <boost/filesystem.hpp>

using namespace Ishiko::Tests;

ChildProcessBuilderTests::ChildProcessBuilderTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ChildProcessBuilder tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("start test 1", StartTest1);
    append<FileComparisonTest>("redirectStandardOutputToFile test 1", RedirectStandardOutputToFileTest1);
    append<HeapAllocationErrorsTest>("StartProcess test 1", StartProcessTest1);
}

void ChildProcessBuilderTests::ConstructorTest1(Test& test)
{
    Ishiko::Process::ChildProcessBuilder builder("dummy");
    
    ISHTF_PASS();
}

void ChildProcessBuilderTests::StartTest1(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper.exe");
#endif

    Ishiko::Process::ChildProcessBuilder builder(executablePath.string());

    Ishiko::Process::ChildProcess handle;
    int err = builder.start(handle);

    ISHTF_ABORT_IF_NEQ(err, 0);
    
    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}

void ChildProcessBuilderTests::RedirectStandardOutputToFileTest1(FileComparisonTest& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/StandardOutputTestHelper.exe");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProcessCreatorRedirectStandardOutputTest1.txt");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "ProcessCreatorRedirectStandardOutputTest1.txt");

    Ishiko::Process::ChildProcessBuilder creator(executablePath.string());
    creator.redirectStandardOutputToFile(outputPath.string());

    Ishiko::Process::ChildProcess handle;
    int err = creator.start(handle);

    ISHTF_ABORT_IF_NEQ(err, 0);
    
    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}

void ChildProcessBuilderTests::StartProcessTest1(Test& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper.exe");

    Ishiko::Process::ChildProcess handle;
    int err = Ishiko::Process::ChildProcessBuilder::StartProcess(executablePath.string(), handle);
    
    ISHTF_ABORT_IF_NEQ(err, 0);

    handle.waitForExit();
    
    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}
