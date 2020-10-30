/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ChildProcessTests.h"
#include "Ishiko/Process/ChildProcess.h"

using namespace Ishiko;
using namespace Ishiko::Process;
using namespace Ishiko::Tests;

ChildProcessTests::ChildProcessTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ChildProcess tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Spawn test 1", SpawnTest1);
    append<HeapAllocationErrorsTest>("Spawn test 2", SpawnTest2);
}

void ChildProcessTests::ConstructorTest1(Test& test)
{
    ChildProcess handle;
    
    ISHTF_PASS();
}

void ChildProcessTests::SpawnTest1(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper.exe");
#endif

    ChildProcess handle = ChildProcess::Spawn(executablePath.string());

    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}

void ChildProcessTests::SpawnTest2(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper.exe");
#endif

    Error error(0);
    ChildProcess handle = ChildProcess::Spawn(executablePath.string(), error);

    ISHTF_ABORT_IF(error);

    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}
