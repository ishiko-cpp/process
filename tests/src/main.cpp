/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "CommandLineTests.h"
#include "CurrentEnvironmentTests.h"
#include "CurrentProcessTests.h"
#include "EnvironmentTests.h"
#include "EnvironmentVariableTests.h"
#include "ProcessTests/ChildProcessTests.h"
#include "ProcessTests/ChildProcessBuilderTests.h"
#include <Ishiko/Tests/Core.hpp>
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoProcess");

    theTestHarness.environment().setTestDataDirectory("../../TestData");
    theTestHarness.environment().setTestOutputDirectory("../../TestOutput");
    boost::filesystem::create_directories("../../TestOutput");
    theTestHarness.environment().setReferenceDataDirectory("../../ReferenceData");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<CurrentEnvironmentTests>();
    theTests.append<CurrentProcessTests>();
    theTests.append<CommandLineTests>();
    theTests.append<EnvironmentVariableTests>();
    theTests.append<EnvironmentTests>();
    theTests.append<ChildProcessTests>();
    theTests.append<ChildProcessBuilderTests>();

    return theTestHarness.run();
}
