/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "EnvironmentTests.h"
#include "Ishiko/Process/Environment.h"
#include "Ishiko/Process/CurrentEnvironment.h"
#include <boost/filesystem/operations.hpp>
#include <fstream>

using namespace Ishiko::Tests;

EnvironmentTests::EnvironmentTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Environment tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("set test 1", SetTest1);
    append<HeapAllocationErrorsTest>("set test 2", SetTest2);
    append<HeapAllocationErrorsTest>("set test 3", SetTest3);
    append<HeapAllocationErrorsTest>("find test 1", FindTest1);
    append<HeapAllocationErrorsTest>("toEnvironmentArray test 1", ToEnvironmentArrayTest1);
    append<HeapAllocationErrorsTest>("toEnvironmentArray test 2", ToEnvironmentArrayTest2);
    append<FileComparisonTest>("toEnvironmentBlock test 1", ToEnvironmentBlockTest1);
    append<FileComparisonTest>("toEnvironmentBlock test 2", ToEnvironmentBlockTest2);
}

void EnvironmentTests::ConstructorTest1(Test& test)
{
    Ishiko::Process::Environment env;

    ISHTF_FAIL_IF_NEQ(env.size(), 0);
    ISHTF_PASS();
}

void EnvironmentTests::ConstructorTest2(Test& test)
{
    Ishiko::Process::CurrentEnvironment::Set("EnvironmentTests_ConstructorTest2_a", "dummy");
    Ishiko::Process::CurrentEnvironment::Set("EnvironmentTests_ConstructorTest2_b", "dummy2");

    Ishiko::Process::Environment env = Ishiko::Process::CurrentEnvironment();

    std::string value1;
    bool found1 = env.find("EnvironmentTests_ConstructorTest2_a", value1);
    std::string value2;
    bool found2 = env.find("EnvironmentTests_ConstructorTest2_b", value2);

    ISHTF_FAIL_IF_NOT(found1);
    ISHTF_FAIL_IF_NEQ(value1, "dummy");
    ISHTF_FAIL_IF_NOT(found2);
    ISHTF_FAIL_IF_NEQ(value2, "dummy2");
    ISHTF_PASS();
}

void EnvironmentTests::SetTest1(Test& test)
{
    Ishiko::Process::Environment env;

    env.set("name", "value");

    std::string value;
    bool found = env.find("name", value);

    ISHTF_FAIL_IF_NEQ(env.size(), 1);
    ISHTF_FAIL_IF_NOT(found);
    ISHTF_FAIL_IF_NEQ(value, "value");
    ISHTF_PASS();
}

void EnvironmentTests::SetTest2(Test& test)
{
    Ishiko::Process::Environment env;

    env.set("name", "value");
    env.set("name", "new_value");

    std::string value;
    bool found = env.find("name", value);

    ISHTF_FAIL_IF_NEQ(env.size(), 1);
    ISHTF_FAIL_IF_NOT(found);
    ISHTF_FAIL_IF_NEQ(value, "new_value");
    ISHTF_PASS();
}

void EnvironmentTests::SetTest3(Test& test)
{
    Ishiko::Process::Environment env;

    env.set("name1", "value1");
    env.set("name3", "value3");
    env.set("name2", "value2");

    ISHTF_FAIL_IF_NEQ(env.size(), 3);
    ISHTF_FAIL_IF_STR_NEQ(env[0].m_variable, "name1=value1");
    ISHTF_FAIL_IF_STR_NEQ(env[1].m_variable, "name2=value2");
    ISHTF_FAIL_IF_STR_NEQ(env[2].m_variable, "name3=value3");
    ISHTF_PASS();
}

void EnvironmentTests::FindTest1(Test& test)
{
    Ishiko::Process::Environment env;

    std::string value;
    bool found = env.find("doesntexist", value);

    ISHTF_FAIL_IF(found);
    ISHTF_FAIL_IF_NEQ(value, "");
    ISHTF_PASS();
}

void EnvironmentTests::ToEnvironmentArrayTest1(Test& test)
{
    Ishiko::Process::Environment env;

    char** environmentArray = env.toEnvironmentArray();

    ISHTF_FAIL_IF_NEQ(environmentArray[0], nullptr);
    ISHTF_PASS();
}

void EnvironmentTests::ToEnvironmentArrayTest2(Test& test)
{
    Ishiko::Process::Environment env;
    env.set("name1", "value1");

    char** environmentArray = env.toEnvironmentArray();

    ISHTF_FAIL_IF_STR_NEQ(environmentArray[0], "name1=value1");
    ISHTF_FAIL_IF_NEQ(environmentArray[1], nullptr);
    ISHTF_PASS();
}

void EnvironmentTests::ToEnvironmentBlockTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "EnvironmentTests_ToEnvironmentBlockTest1.bin");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / 
        "EnvironmentTests_ToEnvironmentBlockTest1.bin");

    Ishiko::Process::Environment env;

    std::vector<char> environmentBlock = env.toEnvironmentBlock();

    std::ofstream output(outputPath.string());
    output.write(environmentBlock.data(), environmentBlock.size());

    ISHTF_PASS();
}

void EnvironmentTests::ToEnvironmentBlockTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "EnvironmentTests_ToEnvironmentBlockTest2.bin");
    boost::filesystem::remove(outputPath);
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() /
        "EnvironmentTests_ToEnvironmentBlockTest2.bin");

    Ishiko::Process::Environment env;
    env.set("name1", "value1");

    std::vector<char> environmentBlock = env.toEnvironmentBlock();

    std::ofstream output(outputPath.string());
    output.write(environmentBlock.data(), environmentBlock.size());

    ISHTF_PASS();
}
