/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "UtilitiesTests.h"
#include "Ishiko/Process/Utilities.h"

using namespace Ishiko;
using namespace Ishiko::Process;
using namespace Ishiko::Tests;

UtilitiesTests::UtilitiesTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Utilities tests", environment)
{
    append<HeapAllocationErrorsTest>("Spawn test 1", SpawnTest1);
    append<HeapAllocationErrorsTest>("Spawn test 2", SpawnTest2);
}

void UtilitiesTests::SpawnTest1(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper.exe");
#endif

    ChildProcess handle = Spawn(executablePath.string());

    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}

void UtilitiesTests::SpawnTest2(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper");
#else
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Bin/ExitCodeTestHelper.exe");
#endif

    Error error(0);
    ChildProcess handle = Spawn(executablePath.string(), error);

    ISHTF_ABORT_IF(error);

    handle.waitForExit();

    ISHTF_FAIL_IF_NEQ(handle.exitCode(), 0);
    ISHTF_PASS();
}
