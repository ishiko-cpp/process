/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ChildProcessBuilderTests.h"
#include "Ishiko/Process/ChildProcessBuilder.h"
#include <boost/filesystem.hpp>

using namespace Ishiko;
using namespace Ishiko::Process;
using namespace Ishiko::Tests;

ChildProcessBuilderTests::ChildProcessBuilderTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ChildProcessBuilder tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("start test 1", StartTest1);
    append<HeapAllocationErrorsTest>("start test 2", StartTest2);
    append<FileComparisonTest>("redirectStandardOutputToFile test 1", RedirectStandardOutputToFileTest1);
    append<FileComparisonTest>("start test 3", StartTest3);
    append<HeapAllocationErrorsTest>("StartProcess test 1", StartProcessTest1);
}

void ChildProcessBuilderTests::ConstructorTest1(Test& test)
{
    ChildProcessBuilder builder("dummy");
    
    ISHTF_PASS();
}

void ChildProcessBuilderTests::StartTest1(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper.exe");
#endif

    ChildProcessBuilder builder(executablePath.string());

    Error error(0);
    ChildProcess handle = builder.start(error);

    ISHTF_ABORT_IF(error);
    
    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}

void ChildProcessBuilderTests::StartTest2(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper.exe");
#endif

    CommandLine command(executablePath, {"1"});
    ChildProcessBuilder builder(command);

    Error error(0);
    ChildProcess handle = builder.start(error);

    ISHTF_ABORT_IF(error);

    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 1);
    ISHTF_PASS();
}

void ChildProcessBuilderTests::RedirectStandardOutputToFileTest1(FileComparisonTest& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/StandardOutputTestHelper.exe");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProcessCreatorRedirectStandardOutputTest1.txt");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "ProcessCreatorRedirectStandardOutputTest1.txt");

    ChildProcessBuilder creator(executablePath.string());
    creator.redirectStandardOutputToFile(outputPath.string());

    Error error(0);
    ChildProcess handle = creator.start(error);

    ISHTF_ABORT_IF(error);
    
    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}

void ChildProcessBuilderTests::StartTest3(FileComparisonTest& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/StandardOutputTestHelper.exe");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "StartTest3.txt");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "StartTest3.txt");

    CommandLine command(executablePath, {"Hello World!"});
    ChildProcessBuilder builder(command);
    builder.redirectStandardOutputToFile(outputPath.string());

    Error error(0);
    ChildProcess handle = builder.start(error);

    ISHTF_ABORT_IF(error);

    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}

void ChildProcessBuilderTests::StartProcessTest1(Test& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper.exe");

    Error error(0);
    ChildProcess handle = ChildProcessBuilder::StartProcess(executablePath.string(), error);
    
    ISHTF_ABORT_IF(error);

    handle.waitForExit();
    
    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}
