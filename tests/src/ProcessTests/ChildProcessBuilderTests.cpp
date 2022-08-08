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
    append<HeapAllocationErrorsTest>("redirectStandardOutputToFile test 1", RedirectStandardOutputToFileTest1);
    append<HeapAllocationErrorsTest>("start test 4", StartTest4);
    append<HeapAllocationErrorsTest>("start test 5", StartTest5);
    append<HeapAllocationErrorsTest>("start test 6", StartTest6);
}

void ChildProcessBuilderTests::ConstructorTest1(Test& test)
{
    ChildProcessBuilder builder("dummy");
    
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest1(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath{test.context().getDataPath("bin/ExitCodeTestHelper")};
#else
    boost::filesystem::path executablePath{test.context().getDataPath( "bin/ExitCodeTestHelper.exe")};
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
    boost::filesystem::path executablePath{test.context().getDataPath("bin/ExitCodeTestHelper")};
#else
    boost::filesystem::path executablePath{test.context().getDataPath("bin/ExitCodeTestHelper.exe")};
#endif

    ChildProcessBuilder builder(executablePath.string());

    Error error;
    ChildProcess handle = builder.start(error);

    ISHIKO_TEST_ABORT_IF(error);

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest3(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath{test.context().getDataPath("bin/ExitCodeTestHelper")};
#else
    boost::filesystem::path executablePath{test.context().getDataPath("bin/ExitCodeTestHelper.exe")};
#endif

    CommandLine command(executablePath, {"1"});
    ChildProcessBuilder builder(command);

    ChildProcess handle = builder.start();

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 1);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::RedirectStandardOutputToFileTest1(Test& test)
{
    const char* basename{"ProcessCreatorRedirectStandardOutputTest1.txt"};

#ifdef __linux__
    boost::filesystem::path executablePath{test.context().getDataPath("bin/StandardOutputTestHelper")};
#else
    boost::filesystem::path executablePath{test.context().getDataPath("bin/StandardOutputTestHelper.exe")};
#endif

    ChildProcessBuilder creator{executablePath.string()};
    creator.redirectStandardOutputToFile(test.context().getOutputPath(basename).string());

    Error error;
    ChildProcess handle = creator.start(error);

    ISHIKO_TEST_ABORT_IF(error);
    
    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest4(Test& test)
{
    const char* basename{"ChildProcessBuilderTests_StartTest4.txt"};

#ifdef __linux__
    boost::filesystem::path executablePath{test.context().getDataPath("bin/StandardOutputTestHelper")};
#else
    boost::filesystem::path executablePath{test.context().getDataPath("bin/StandardOutputTestHelper.exe")};
#endif

    CommandLine command(executablePath, {"Hello World!"});
    ChildProcessBuilder builder(command);
    builder.redirectStandardOutputToFile(test.context().getOutputPath(basename).string());

    ChildProcess handle = builder.start();

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest5(Test& test)
{
    const char* basename{"ChildProcessBuilderTests_StartTest5.txt"};

#ifdef __linux__
    boost::filesystem::path executablePath{test.context().getDataPath("bin/DumpTestHelper")};
#else
    boost::filesystem::path executablePath{test.context().getDataPath("bin/DumpTestHelper.exe")};
#endif

    CommandLine command(executablePath.string());
    ChildProcessBuilder builder(command, Environment());
    builder.redirectStandardOutputToFile(test.context().getOutputPath(basename).string());

    ChildProcess handle = builder.start();

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void ChildProcessBuilderTests::StartTest6(Test& test)
{
    const char* basename{"ChildProcessBuilderTests_StartTest6.txt"};

#ifdef __linux__
    boost::filesystem::path executablePath{test.context().getDataPath("bin/DumpTestHelper")};
#else
    boost::filesystem::path executablePath{test.context().getDataPath("bin/DumpTestHelper.exe")};
#endif

    CommandLine command(executablePath.string());
    Environment environment;
    environment.set("name1", "value1");
    ChildProcessBuilder builder(command, environment);
    builder.redirectStandardOutputToFile(test.context().getOutputPath(basename).string());

    ChildProcess handle = builder.start();

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}
