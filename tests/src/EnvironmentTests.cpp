// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "EnvironmentTests.h"
#include "Ishiko/Process/Environment.hpp"
#include "Ishiko/Process/CurrentEnvironment.hpp"
#include <boost/filesystem/operations.hpp>
#include <fstream>

using namespace Ishiko;

EnvironmentTests::EnvironmentTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Environment tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("set test 1", SetTest1);
    append<HeapAllocationErrorsTest>("set test 2", SetTest2);
    append<HeapAllocationErrorsTest>("set test 3", SetTest3);
    append<HeapAllocationErrorsTest>("find test 1", FindTest1);
    append<HeapAllocationErrorsTest>("toEnvironmentArray test 1", ToEnvironmentArrayTest1);
    append<HeapAllocationErrorsTest>("toEnvironmentArray test 2", ToEnvironmentArrayTest2);
    append<HeapAllocationErrorsTest>("toEnvironmentBlock test 1", ToEnvironmentBlockTest1);
    append<HeapAllocationErrorsTest>("toEnvironmentBlock test 2", ToEnvironmentBlockTest2);
}

void EnvironmentTests::ConstructorTest1(Test& test)
{
    Environment env;

    ISHIKO_TEST_FAIL_IF_NEQ(env.size(), 0);
    ISHIKO_TEST_PASS();
}

void EnvironmentTests::ConstructorTest2(Test& test)
{
    CurrentEnvironment::Set("EnvironmentTests_ConstructorTest2_a", "dummy");
    CurrentEnvironment::Set("EnvironmentTests_ConstructorTest2_b", "dummy2");

    Environment env = CurrentEnvironment();

    std::string value1;
    bool found1 = env.find("EnvironmentTests_ConstructorTest2_a", value1);
    std::string value2;
    bool found2 = env.find("EnvironmentTests_ConstructorTest2_b", value2);

    ISHIKO_TEST_FAIL_IF_NOT(found1);
    ISHIKO_TEST_FAIL_IF_NEQ(value1, "dummy");
    ISHIKO_TEST_FAIL_IF_NOT(found2);
    ISHIKO_TEST_FAIL_IF_NEQ(value2, "dummy2");
    ISHIKO_TEST_PASS();
}

void EnvironmentTests::SetTest1(Test& test)
{
    Environment env;

    env.set("name", "value");

    std::string value;
    bool found = env.find("name", value);

    ISHIKO_TEST_FAIL_IF_NEQ(env.size(), 1);
    ISHIKO_TEST_FAIL_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(value, "value");
    ISHIKO_TEST_PASS();
}

void EnvironmentTests::SetTest2(Test& test)
{
    Environment env;

    env.set("name", "value");
    env.set("name", "new_value");

    std::string value;
    bool found = env.find("name", value);

    ISHIKO_TEST_FAIL_IF_NEQ(env.size(), 1);
    ISHIKO_TEST_FAIL_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(value, "new_value");
    ISHIKO_TEST_PASS();
}

void EnvironmentTests::SetTest3(Test& test)
{
    Environment env;

    env.set("name1", "value1");
    env.set("name3", "value3");
    env.set("name2", "value2");

    ISHIKO_TEST_FAIL_IF_NEQ(env.size(), 3);
    ISHIKO_TEST_FAIL_IF_STR_NEQ(env[0].variable(), "name1=value1");
    ISHIKO_TEST_FAIL_IF_STR_NEQ(env[1].variable(), "name2=value2");
    ISHIKO_TEST_FAIL_IF_STR_NEQ(env[2].variable(), "name3=value3");
    ISHIKO_TEST_PASS();
}

void EnvironmentTests::FindTest1(Test& test)
{
    Environment env;

    std::string value;
    bool found = env.find("doesntexist", value);

    ISHIKO_TEST_FAIL_IF(found);
    ISHIKO_TEST_FAIL_IF_NEQ(value, "");
    ISHIKO_TEST_PASS();
}

void EnvironmentTests::ToEnvironmentArrayTest1(Test& test)
{
    Environment env;

    char** environmentArray = env.toEnvironmentArray();

    ISHIKO_TEST_FAIL_IF_NEQ(environmentArray[0], nullptr);
    ISHIKO_TEST_PASS();
}

void EnvironmentTests::ToEnvironmentArrayTest2(Test& test)
{
    Environment env;
    env.set("name1", "value1");

    char** environmentArray = env.toEnvironmentArray();

    ISHIKO_TEST_FAIL_IF_STR_NEQ(environmentArray[0], "name1=value1");
    ISHIKO_TEST_FAIL_IF_NEQ(environmentArray[1], nullptr);
    ISHIKO_TEST_PASS();
}

void EnvironmentTests::ToEnvironmentBlockTest1(Test& test)
{
    const char* basename{"EnvironmentTests_ToEnvironmentBlockTest1.bin"};

    Environment env;

    std::vector<char> environmentBlock = env.toEnvironmentBlock();

    std::ofstream output{test.context().getOutputPath(basename).string()};
    output.write(environmentBlock.data(), environmentBlock.size());
    output.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void EnvironmentTests::ToEnvironmentBlockTest2(Test& test)
{
    const char* basename{"EnvironmentTests_ToEnvironmentBlockTest2.bin"};

    Environment env;
    env.set("name1", "value1");

    std::vector<char> environmentBlock = env.toEnvironmentBlock();

    std::ofstream output{test.context().getOutputPath(basename).string()};
    output.write(environmentBlock.data(), environmentBlock.size());
    output.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}
