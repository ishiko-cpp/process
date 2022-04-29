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
#include "Ishiko/Process/linkoptions.h"
#include <Ishiko/TestFramework/Core.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoProcess");

    theTestHarness.context().setTestDataDirectory("../../data");
    theTestHarness.context().setTestOutputDirectory("../../output");
    theTestHarness.context().setReferenceDataDirectory("../../reference");

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
