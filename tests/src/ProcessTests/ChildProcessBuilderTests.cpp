/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "ChildProcessBuilderTests.h"
#include "Ishiko/Process/ChildProcessBuilder.h"
#include <boost/filesystem.hpp>

using namespace Ishiko;

ChildProcessBuilderTests::ChildProcessBuilderTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ChildProcessBuilder tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("start test 1", StartTest1);
    append<HeapAllocationErrorsTest>("start test 2", StartTest2);
    append<HeapAllocationErrorsTest>("start test 3", StartTest3);
    append<FileComparisonTest>("redirectStandardOutputToFile test 1", RedirectStandardOutputToFileTest1);
    append<FileComparisonTest>("start test 4", StartTest4);
    append<FileComparisonTest>("start test 5", StartTest5);
    append<FileComparisonTest>("start test 6", StartTest6);
}

void ChildProcessBuilderTests::ConstructorTest1(Test& test)
{
    ChildProcessBuilder builder("dummy");
    
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest1(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath = test.context().getDataPath("bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath = test.context().getDataPath( "bin/ExitCodeTestHelper.exe");
#endif

    ChildProcessBuilder builder(executablePath.string());

    ChildProcess handle = builder.start();

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest2(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath = test.context().getDataPath("bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath = test.context().getDataPath("bin/ExitCodeTestHelper.exe");
#endif

    ChildProcessBuilder builder(executablePath.string());

    Error error(0);
    ChildProcess handle = builder.start(error);

    ISHIKO_TEST_ABORT_IF(error);

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest3(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath = test.context().getDataPath("bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath = test.context().getDataPath("bin/ExitCodeTestHelper.exe");
#endif

    CommandLine command(executablePath, {"1"});
    ChildProcessBuilder builder(command);

    ChildProcess handle = builder.start();

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 1);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::RedirectStandardOutputToFileTest1(FileComparisonTest& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.context().getTestDataDirectory() / "bin/StandardOutputTestHelper");
#else
    boost::filesystem::path executablePath(test.context().getTestDataDirectory() / "bin/StandardOutputTestHelper.exe");
#endif
    boost::filesystem::path outputPath(test.context().getTestOutputDirectory() / "ProcessCreatorRedirectStandardOutputTest1.txt");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataDirectory() / "ProcessCreatorRedirectStandardOutputTest1.txt");

    ChildProcessBuilder creator(executablePath.string());
    creator.redirectStandardOutputToFile(outputPath.string());

    Error error(0);
    ChildProcess handle = creator.start(error);

    ISHIKO_TEST_ABORT_IF(error);
    
    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest4(FileComparisonTest& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.context().getTestDataDirectory() / "bin/StandardOutputTestHelper");
#else
    boost::filesystem::path executablePath(test.context().getTestDataDirectory() / "bin/StandardOutputTestHelper.exe");
#endif
    boost::filesystem::path outputPath(test.context().getTestOutputDirectory() / "ChildProcessBuilderTests_StartTest4.txt");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataDirectory() / "ChildProcessBuilderTests_StartTest4.txt");

    CommandLine command(executablePath, {"Hello World!"});
    ChildProcessBuilder builder(command);
    builder.redirectStandardOutputToFile(outputPath.string());

    ChildProcess handle = builder.start();

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest5(FileComparisonTest& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.context().getTestDataDirectory() / "bin/DumpTestHelper");
#else
    boost::filesystem::path executablePath(test.context().getTestDataDirectory() / "bin/DumpTestHelper.exe");
#endif
    boost::filesystem::path outputPath(test.context().getTestOutputDirectory() / "ChildProcessBuilderTests_StartTest5.txt");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataDirectory() / "ChildProcessBuilderTests_StartTest5.txt");

    CommandLine command(executablePath.string());
    ChildProcessBuilder builder(command, Environment());
    builder.redirectStandardOutputToFile(outputPath.string());

    ChildProcess handle = builder.start();

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest6(FileComparisonTest& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.context().getTestDataDirectory() / "bin/DumpTestHelper");
#else
    boost::filesystem::path executablePath(test.context().getTestDataDirectory() / "bin/DumpTestHelper.exe");
#endif
    boost::filesystem::path outputPath(test.context().getTestOutputDirectory() / "ChildProcessBuilderTests_StartTest6.txt");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataDirectory() / "ChildProcessBuilderTests_StartTest6.txt");

    CommandLine command(executablePath.string());
    Environment environment;
    environment.set("name1", "value1");
    ChildProcessBuilder builder(command, environment);
    builder.redirectStandardOutputToFile(outputPath.string());

    ChildProcess handle = builder.start();

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_PASS();
}
