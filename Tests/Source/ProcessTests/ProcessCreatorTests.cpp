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
#include <boost/filesystem.hpp>

void AddProcessCreatorTests(TestHarness& theTestHarness)
{
    TestSequence& processTestSequence = theTestHarness.appendTestSequence("ProcessCreator tests");

    new HeapAllocationErrorsTest("Creation test 1", ProcessCreatorCreationTest1, processTestSequence);

    new HeapAllocationErrorsTest("start test 1", ProcessCreatorStartTest1, processTestSequence);

    new FileComparisonTest("redirectStandardOutputToFile test 1", ProcessCreatorRedirectStandardOutputToFileTest1, processTestSequence);

    new HeapAllocationErrorsTest("StartProcess test 1", ProcessCreatorStartProcessTest1, processTestSequence);
}

TestResult::EOutcome ProcessCreatorCreationTest1()
{
    Ishiko::Process::ProcessCreator creator("dummy");
    return TestResult::ePassed;
}

TestResult::EOutcome ProcessCreatorStartTest1(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Binaries/ExitCodeTestHelper.exe");

    Ishiko::Process::ProcessCreator creator(executablePath.string());

    Ishiko::Process::ProcessHandle handle;
    int err = creator.start(handle);
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

TestResult::EOutcome ProcessCreatorRedirectStandardOutputToFileTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Binaries/StandardOutputTestHelper.exe");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProcessCreatorRedirectStandardOutputTest1.txt");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "ProcessCreatorRedirectStandardOutputTest1.txt");

    Ishiko::Process::ProcessCreator creator(executablePath.string());
    creator.redirectStandardOutputToFile(outputPath.string());

    Ishiko::Process::ProcessHandle handle;
    int err = creator.start(handle);
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
