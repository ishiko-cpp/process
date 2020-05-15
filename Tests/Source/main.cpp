/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "EnvironmentTests/EnvironmentTests.h"
#include "ProcessTests/ProcessHandleTests.h"
#include "ProcessTests/ProcessCreatorTests.h"
#include "Ishiko/TestFramework/TestFrameworkCore.h"
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
    theTests.append<EnvironmentTests>();
    theTests.append<ProcessHandleTests>();
    theTests.append<ProcessCreatorTests>();

    return theTestHarness.run();
}
