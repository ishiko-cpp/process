/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ProcessHandleTests.h"
#include "Ishiko/Process/ProcessHandle.h"

using namespace Ishiko::Tests;

ProcessHandleTests::ProcessHandleTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ProcessHandle tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void ProcessHandleTests::ConstructorTest1(Test& test)
{
    Ishiko::Process::ProcessHandle handle;
    
    ISHTF_PASS();
}
