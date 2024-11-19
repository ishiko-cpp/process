// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "CommandLineTests.hpp"
#include "CurrentEnvironmentTests.h"
#include "CurrentProcessTests.h"
#include "EnvironmentTests.h"
#include "EnvironmentVariableTests.h"
#include "ProcessTests/ChildProcessTests.h"
#include "ProcessTests/ChildProcessBuilderTests.h"
#include "Ishiko/Process/linkoptions.hpp"
#include <Ishiko/TestFramework/Core.hpp>
#include <exception>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    try
    {
        TestHarness::CommandLineSpecification command_line_spec;
        Configuration configuration = command_line_spec.createDefaultConfiguration();
        configuration.set("context.data", "../../data");
        configuration.set("context.output", "../../output");
        configuration.set("context.reference", "../../reference");
        CommandLineParser::parse(command_line_spec, argc, argv, configuration);

        TestHarness the_test_harness("IshikoProcess Library Tests", configuration);

        TestSequence& the_tests = the_test_harness.tests();
        the_tests.append<CurrentEnvironmentTests>();
        the_tests.append<CurrentProcessTests>();
        the_tests.append<CommandLineTests>();
        the_tests.append<EnvironmentVariableTests>();
        the_tests.append<EnvironmentTests>();
        the_tests.append<ChildProcessTests>();
        the_tests.append<ChildProcessBuilderTests>();

        return the_test_harness.run();
    }
    catch (const std::exception& e)
    {
        return TestApplicationReturnCode::exception;
    }
    catch (...)
    {
        return TestApplicationReturnCode::exception;
    }
}
