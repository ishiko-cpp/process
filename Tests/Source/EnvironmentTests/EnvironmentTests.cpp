/*
    Copyright (c) 2015-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "EnvironmentTests.h"
#include "Ishiko/Process/Environment.h"

using namespace Ishiko::Tests;

EnvironmentTests::EnvironmentTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Environment tests", environment)
{
	append<HeapAllocationErrorsTest>("set test 1", SetTest1);
    append<HeapAllocationErrorsTest>("set test 2", SetTest2);
    append<HeapAllocationErrorsTest>("find test 1", FindTest1);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 1", ExpandVariablesInStringTest1);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 2", ExpandVariablesInStringTest2);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 3", ExpandVariablesInStringTest3);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 4", ExpandVariablesInStringTest4);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 5", ExpandVariablesInStringTest5);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 6", ExpandVariablesInStringTest6);
}

void EnvironmentTests::SetTest1(Test& test)
{
	Ishiko::Process::Environment::set("IshikoEnvironmentSetTest1", "dummy");
	
	std::string value;
	bool found = Ishiko::Process::Environment::find("IshikoEnvironmentSetTest1", value);

    ISHTF_FAIL_IF_NOT(found);
    ISHTF_FAIL_IF_NEQ(value, "dummy");
    ISHTF_PASS();
}

void EnvironmentTests::SetTest2(Test& test)
{
	Ishiko::Process::Environment::set("IshikoEnvironmentSetTest2", "dummy");
	Ishiko::Process::Environment::set("IshikoEnvironmentSetTest2", "dummy2");

	std::string value;
	bool found = Ishiko::Process::Environment::find("IshikoEnvironmentSetTest2", value);

    ISHTF_FAIL_IF_NOT(found);
    ISHTF_FAIL_IF_NEQ(value, "dummy2");
    ISHTF_PASS();
}

void EnvironmentTests::FindTest1(Test& test)
{
	std::string value;
	bool found = Ishiko::Process::Environment::find("IshikoEnvironmentFindTest1", value);

    ISHTF_FAIL_IF(found);
    ISHTF_PASS();
}

void EnvironmentTests::ExpandVariablesInStringTest1(Test& test)
{
	std::string str = "dummy";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);

    ISHTF_FAIL_IF_NEQ(str, expandedStr);
    ISHTF_PASS();
}

void EnvironmentTests::ExpandVariablesInStringTest2(Test& test)
{
	Ishiko::Process::Environment::set("EnvironmentExpandVariablesInStringTest2", "dummy");

	std::string str = "$(EnvironmentExpandVariablesInStringTest2)";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);

    ISHTF_FAIL_IF_NEQ(expandedStr, "dummy");
    ISHTF_PASS();
}

void EnvironmentTests::ExpandVariablesInStringTest3(Test& test)
{
	Ishiko::Process::Environment::set("EnvironmentExpandVariablesInStringTest3", "dummy");

	std::string str = "this is a $(EnvironmentExpandVariablesInStringTest3) environment variable";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);

    ISHTF_FAIL_IF_NEQ(expandedStr, "this is a dummy environment variable");
    ISHTF_PASS();
}

void EnvironmentTests::ExpandVariablesInStringTest4(Test& test)
{
	Ishiko::Process::Environment::set("EnvironmentExpandVariablesInStringTest4_1", "dummy1");
	Ishiko::Process::Environment::set("EnvironmentExpandVariablesInStringTest4_2", "dummy2");

	std::string str = "These are $(EnvironmentExpandVariablesInStringTest4_1) and $(EnvironmentExpandVariablesInStringTest4_2)!";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);

    ISHTF_FAIL_IF_NEQ(expandedStr, "These are dummy1 and dummy2!");
    ISHTF_PASS();
}

void EnvironmentTests::ExpandVariablesInStringTest5(Test& test)
{
	std::string str = "this is a $(nonexistent) environment variable";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);

    ISHTF_FAIL_IF_NEQ(expandedStr, "this is a $(nonexistent) environment variable");
    ISHTF_PASS();
}

void EnvironmentTests::ExpandVariablesInStringTest6(Test& test)
{
	std::string str = "this is a $(incomplete environment variable";
	std::string expandedStr =
		Ishiko::Process::Environment::expandVariablesInString(
		str, Ishiko::Process::Environment::eDollarAndParentheses);

    ISHTF_FAIL_IF_NEQ(expandedStr, "this is a $(incomplete environment variable");
    ISHTF_PASS();
}
