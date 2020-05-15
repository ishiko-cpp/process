/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ProcessCreatorTests.h"
#include "Ishiko/Process/ProcessCreator.h"
#include <boost/filesystem.hpp>

using namespace Ishiko::Tests;

ProcessCreatorTests::ProcessCreatorTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ProcessCreator tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("start test 1", StartTest1);
    append<FileComparisonTest>("redirectStandardOutputToFile test 1", RedirectStandardOutputToFileTest1);
    append<HeapAllocationErrorsTest>("StartProcess test 1", StartProcessTest1);
}

void ProcessCreatorTests::ConstructorTest1(Test& test)
{
    Ishiko::Process::ProcessCreator creator("dummy");
    
    ISHTF_PASS();
}

void ProcessCreatorTests::StartTest1(Test& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Binaries/ExitCodeTestHelper.exe");

    Ishiko::Process::ProcessCreator creator(executablePath.string());

    Ishiko::Process::ProcessHandle handle;
    int err = creator.start(handle);

    ISHTF_ABORT_IF_NEQ(err, 0);
    
    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}

void ProcessCreatorTests::RedirectStandardOutputToFileTest1(FileComparisonTest& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Binaries/StandardOutputTestHelper.exe");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProcessCreatorRedirectStandardOutputTest1.txt");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "ProcessCreatorRedirectStandardOutputTest1.txt");

    Ishiko::Process::ProcessCreator creator(executablePath.string());
    creator.redirectStandardOutputToFile(outputPath.string());

    Ishiko::Process::ProcessHandle handle;
    int err = creator.start(handle);

    ISHTF_ABORT_IF_NEQ(err, 0);
    
    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}

void ProcessCreatorTests::StartProcessTest1(Test& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Binaries/ExitCodeTestHelper.exe");

    Ishiko::Process::ProcessHandle handle;
    int err = Ishiko::Process::ProcessCreator::StartProcess(executablePath.string(), handle);
    
    ISHTF_ABORT_IF_NEQ(err, 0);

    handle.waitForExit();
    
    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}
