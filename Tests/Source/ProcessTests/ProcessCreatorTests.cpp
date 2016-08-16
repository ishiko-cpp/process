/*
    Copyright (c) 2016 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "ProcessCreatorTests.h"
#include "Ishiko/Process/ProcessCreator.h"

void AddProcessCreatorTests(TestHarness& theTestHarness)
{
    TestSequence& processTestSequence = theTestHarness.appendTestSequence("ProcessCreator tests");

    new HeapAllocationErrorsTest("StartProcess test 1", ProcessCreatorStartProcessTest1, processTestSequence);
}

TestResult::EOutcome ProcessCreatorStartProcessTest1(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Binaries/ExitCodeTestHelper.exe");

    Ishiko::Process::ProcessHandle handle;
    int err = Ishiko::Process::ProcessCreator::StartProcess(executablePath.string(), handle);
    if (err == 0)
    {
        handle.waitForExit();
        if (handle.exitCode() == 0)
        {
            result = TestResult::ePassed;
        }
    }
    
    return result;
}
