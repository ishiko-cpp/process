/*
    Copyright (c) 2015-2016 Xavier Leclercq

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

#include "EnvironmentTests.h"
#include "Ishiko/Process/Environment.h"

void AddEnvironmentTests(TestHarness& theTestHarness)
{
	TestSequence& environmentTestSequence = theTestHarness.appendTestSequence("Environment tests");

	new HeapAllocationErrorsTest("set test 1", EnvironmentSetTest1, environmentTestSequence);
	new HeapAllocationErrorsTest("set test 2", EnvironmentSetTest2, environmentTestSequence);
	
	new HeapAllocationErrorsTest("find test 1", EnvironmentFindTest1, environmentTestSequence);

	new HeapAllocationErrorsTest("expandVariablesInString test 1", EnvironmentExpandVariablesInStringTest1,
		environmentTestSequence);
	new HeapAllocationErrorsTest("expandVariablesInString test 2", EnvironmentExpandVariablesInStringTest2,
		environmentTestSequence);
	new HeapAllocationErrorsTest("expandVariablesInString test 3", EnvironmentExpandVariablesInStringTest3,
		environmentTestSequence);
	new HeapAllocationErrorsTest("expandVariablesInString test 4", EnvironmentExpandVariablesInStringTest4,
		environmentTestSequence);
	new HeapAllocationErrorsTest("expandVariablesInString test 5", EnvironmentExpandVariablesInStringTest5,
		environmentTestSequence);
	new HeapAllocationErrorsTest("expandVariablesInString test 6", EnvironmentExpandVariablesInStringTest6,
		environmentTestSequence);
}

TestResult::EOutcome EnvironmentSetTest1()
{
	TestResult::EOutcome result = TestResult::eFailed;

	Ishiko::Process::Environment::set("IshikoEnvironmentSetTest1", "dummy");
	
	std::string value;
	bool found = Ishiko::Process::Environment::find("IshikoEnvironmentSetTest1", value);
	if (found && (value == "dummy"))
	{
		result = TestResult::ePassed;
	}

	return result;
}

TestResult::EOutcome EnvironmentSetTest2()
{
	TestResult::EOutcome result = TestResult::eFailed;

	Ishiko::Process::Environment::set("IshikoEnvironmentSetTest2", "dummy");
	Ishiko::Process::Environment::set("IshikoEnvironmentSetTest2", "dummy2");

	std::string value;
	bool found = Ishiko::Process::Environment::find("IshikoEnvironmentSetTest2", value);
	if (found && (value == "dummy2"))
	{
		result = TestResult::ePassed;
	}

	return result;
}

TestResult::EOutcome EnvironmentFindTest1()
{
	std::string value;
	bool found = Ishiko::Process::Environment::find("IshikoEnvironmentFindTest1", value);
	if (!found)
	{
		return TestResult::ePassed;
	}
	else
	{
		return TestResult::eFailed;
	}
}

TestResult::EOutcome EnvironmentExpandVariablesInStringTest1()
{
	std::string str = "dummy";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);
	if (str == expandedStr)
	{
		return TestResult::ePassed;
	}
	else
	{
		return TestResult::eFailed;
	}
}

TestResult::EOutcome EnvironmentExpandVariablesInStringTest2()
{
	Ishiko::Process::Environment::set("EnvironmentExpandVariablesInStringTest2", "dummy");

	std::string str = "$(EnvironmentExpandVariablesInStringTest2)";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);
	if (expandedStr == "dummy")
	{
		return TestResult::ePassed;
	}
	else
	{
		return TestResult::eFailed;
	}
}

TestResult::EOutcome EnvironmentExpandVariablesInStringTest3()
{
	Ishiko::Process::Environment::set("EnvironmentExpandVariablesInStringTest3", "dummy");

	std::string str = "this is a $(EnvironmentExpandVariablesInStringTest3) environment variable";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);
	if (expandedStr == "this is a dummy environment variable")
	{
		return TestResult::ePassed;
	}
	else
	{
		return TestResult::eFailed;
	}
}

TestResult::EOutcome EnvironmentExpandVariablesInStringTest4()
{
	Ishiko::Process::Environment::set("EnvironmentExpandVariablesInStringTest4_1", "dummy1");
	Ishiko::Process::Environment::set("EnvironmentExpandVariablesInStringTest4_2", "dummy2");

	std::string str = "These are $(EnvironmentExpandVariablesInStringTest4_1) and $(EnvironmentExpandVariablesInStringTest4_2)!";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);
	if (expandedStr == "These are dummy1 and dummy2!")
	{
		return TestResult::ePassed;
	}
	else
	{
		return TestResult::eFailed;
	}
}

TestResult::EOutcome EnvironmentExpandVariablesInStringTest5()
{
	std::string str = "this is a $(nonexistent) environment variable";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);
	if (expandedStr == "this is a $(nonexistent) environment variable")
	{
		return TestResult::ePassed;
	}
	else
	{
		return TestResult::eFailed;
	}
}

TestResult::EOutcome EnvironmentExpandVariablesInStringTest6()
{
	std::string str = "this is a $(incomplete environment variable";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);
	if (expandedStr == "this is a $(incomplete environment variable")
	{
		return TestResult::ePassed;
	}
	else
	{
		return TestResult::eFailed;
	}
}
