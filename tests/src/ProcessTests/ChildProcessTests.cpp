// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "ChildProcessTests.h"
#include "Ishiko/Process/ChildProcess.hpp"

using namespace Ishiko;

ChildProcessTests::ChildProcessTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ChildProcess tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Spawn test 1", SpawnTest1);
    append<HeapAllocationErrorsTest>("Spawn test 2", SpawnTest2);
}

void ChildProcessTests::ConstructorTest1(Test& test)
{
    ChildProcess handle;
    
    ISHIKO_TEST_PASS();
}

void ChildProcessTests::SpawnTest1(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath = test.context().getDataPath("bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath = test.context().getDataPath("bin/ExitCodeTestHelper.exe");
#endif

    ChildProcess handle = ChildProcess::Spawn(executablePath.string());

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_PASS();
}

void ChildProcessTests::SpawnTest2(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath = test.context().getDataPath("bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath = test.context().getDataPath("bin/ExitCodeTestHelper.exe");
#endif

    Error error;
    ChildProcess handle = ChildProcess::Spawn(executablePath.string(), error);

    ISHIKO_TEST_ABORT_IF(error);

    handle.waitForExit();

    ISHIKO_TEST_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHIKO_TEST_PASS();
}
