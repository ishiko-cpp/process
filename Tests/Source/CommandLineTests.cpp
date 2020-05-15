/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "CommandLineTests.h"

using namespace Ishiko::Tests;

CommandLineTests::CommandLineTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "CommandLine tests", environment)
{
}
