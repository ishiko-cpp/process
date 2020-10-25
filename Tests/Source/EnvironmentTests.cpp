/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "EnvironmentTests.h"
#include "Ishiko/Process/Environment.h"
#include <boost/filesystem/operations.hpp>
#include <fstream>

using namespace Ishiko::Tests;

EnvironmentTests::EnvironmentTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Environment tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("set test 1", SetTest1);
    append<HeapAllocationErrorsTest>("toEnvironmentArray test 1", ToEnvironmentArrayTest1);
    append<HeapAllocationErrorsTest>("toEnvironmentArray test 2", ToEnvironmentArrayTest2);
    append<FileComparisonTest>("toEnvironmentBlock test 1", ToEnvironmentBlockTest1);
    append<FileComparisonTest>("toEnvironmentBlock test 2", ToEnvironmentBlockTest2);
}

void EnvironmentTests::ConstructorTest1(Test& test)
{
    Ishiko::Process::Environment env;

    ISHTF_PASS();
}

void EnvironmentTests::SetTest1(Test& test)
{
    Ishiko::Process::Environment env;

    env.set("name", "value");

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
