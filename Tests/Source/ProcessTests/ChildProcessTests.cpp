/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ChildProcessTests.h"
#include "Ishiko/Process/ChildProcess.h"

using namespace Ishiko::Tests;

ChildProcessTests::ChildProcessTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ChildProcess tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void ChildProcessTests::ConstructorTest1(Test& test)
{
    Ishiko::Process::ChildProcess handle;
    
    ISHTF_PASS();
}
