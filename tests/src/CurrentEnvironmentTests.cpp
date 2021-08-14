/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "CurrentEnvironmentTests.h"
#include "Ishiko/Process/CurrentEnvironment.h"

using namespace Ishiko::Process;
using namespace Ishiko::Tests;

CurrentEnvironmentTests::CurrentEnvironmentTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "CurrentEnvironment tests", environment)
{
    append<HeapAllocationErrorsTest>("set test 1", SetTest1);
    append<HeapAllocationErrorsTest>("set test 2", SetTest2);
    append<HeapAllocationErrorsTest>("find test 1", FindTest1);
    append<HeapAllocationErrorsTest>("ToMap test 1", ToMapTest1);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 1", ExpandVariablesInStringTest1);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 2", ExpandVariablesInStringTest2);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 3", ExpandVariablesInStringTest3);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 4", ExpandVariablesInStringTest4);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 5", ExpandVariablesInStringTest5);
    append<HeapAllocationErrorsTest>("expandVariablesInString test 6", ExpandVariablesInStringTest6);
}

void CurrentEnvironmentTests::SetTest1(Test& test)
{
	CurrentEnvironment::Set("IshikoEnvironmentSetTest1", "dummy");
	
	std::string value;
	bool found = CurrentEnvironment::Find("IshikoEnvironmentSetTest1", value);

    ISHIKO_FAIL_IF_NOT(found);
    ISHIKO_FAIL_IF_NEQ(value, "dummy");
    ISHIKO_PASS();
}

void CurrentEnvironmentTests::SetTest2(Test& test)
{
	CurrentEnvironment::Set("IshikoEnvironmentSetTest2", "dummy");
	CurrentEnvironment::Set("IshikoEnvironmentSetTest2", "dummy2");

	std::string value;
	bool found = CurrentEnvironment::Find("IshikoEnvironmentSetTest2", value);

    ISHIKO_FAIL_IF_NOT(found);
    ISHIKO_FAIL_IF_NEQ(value, "dummy2");
    ISHIKO_PASS();
}

void CurrentEnvironmentTests::FindTest1(Test& test)
{
	std::string value;
	bool found = CurrentEnvironment::Find("IshikoEnvironmentFindTest1", value);

    ISHIKO_FAIL_IF(found);
    ISHIKO_PASS();
}

void CurrentEnvironmentTests::ToMapTest1(Test& test)
{
    CurrentEnvironment::Set("CurrentEnvironmentTests_ToMapTest1_a", "dummy");
    CurrentEnvironment::Set("CurrentEnvironmentTests_ToMapTest1_b", "dummy2");

    std::map<std::string, std::string> environment = CurrentEnvironment::ToMap();

    ISHIKO_FAIL_IF_NEQ(environment.at("CurrentEnvironmentTests_ToMapTest1_a"), "dummy");
    ISHIKO_FAIL_IF_NEQ(environment.at("CurrentEnvironmentTests_ToMapTest1_b"), "dummy2");
    ISHIKO_PASS();
}

void CurrentEnvironmentTests::ExpandVariablesInStringTest1(Test& test)
{
	std::string str = "dummy";
	std::string expandedStr = CurrentEnvironment::ExpandVariablesInString(str,
        CurrentEnvironment::eDollarAndParentheses);

    ISHIKO_FAIL_IF_NEQ(str, expandedStr);
    ISHIKO_PASS();
}

void CurrentEnvironmentTests::ExpandVariablesInStringTest2(Test& test)
{
	CurrentEnvironment::Set("EnvironmentExpandVariablesInStringTest2", "dummy");

	std::string str = "$(EnvironmentExpandVariablesInStringTest2)";
	std::string expandedStr = CurrentEnvironment::ExpandVariablesInString(str,
        CurrentEnvironment::eDollarAndParentheses);

    ISHIKO_FAIL_IF_NEQ(expandedStr, "dummy");
    ISHIKO_PASS();
}

void CurrentEnvironmentTests::ExpandVariablesInStringTest3(Test& test)
{
	CurrentEnvironment::Set("EnvironmentExpandVariablesInStringTest3", "dummy");

	std::string str = "this is a $(EnvironmentExpandVariablesInStringTest3) environment variable";
	std::string expandedStr = CurrentEnvironment::ExpandVariablesInString(str,
        CurrentEnvironment::eDollarAndParentheses);

    ISHIKO_FAIL_IF_NEQ(expandedStr, "this is a dummy environment variable");
    ISHIKO_PASS();
}

void CurrentEnvironmentTests::ExpandVariablesInStringTest4(Test& test)
{
	CurrentEnvironment::Set("EnvironmentExpandVariablesInStringTest4_1", "dummy1");
	CurrentEnvironment::Set("EnvironmentExpandVariablesInStringTest4_2", "dummy2");

	std::string str = "These are $(EnvironmentExpandVariablesInStringTest4_1) and $(EnvironmentExpandVariablesInStringTest4_2)!";
	std::string expandedStr = CurrentEnvironment::ExpandVariablesInString(str,
        CurrentEnvironment::eDollarAndParentheses);

    ISHIKO_FAIL_IF_NEQ(expandedStr, "These are dummy1 and dummy2!");
    ISHIKO_PASS();
}

void CurrentEnvironmentTests::ExpandVariablesInStringTest5(Test& test)
{
	std::string str = "this is a $(nonexistent) environment variable";
	std::string expandedStr = CurrentEnvironment::ExpandVariablesInString(str,
        CurrentEnvironment::eDollarAndParentheses);

    ISHIKO_FAIL_IF_NEQ(expandedStr, "this is a $(nonexistent) environment variable");
    ISHIKO_PASS();
}

void CurrentEnvironmentTests::ExpandVariablesInStringTest6(Test& test)
{
	std::string str = "this is a $(incomplete environment variable";
	std::string expandedStr = CurrentEnvironment::ExpandVariablesInString(str,
        CurrentEnvironment::eDollarAndParentheses);

    ISHIKO_FAIL_IF_NEQ(expandedStr, "this is a $(incomplete environment variable");
    ISHIKO_PASS();
}
