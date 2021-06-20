/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_TEST_COMMANDLINESPECIFICATIONTESTS_H_
#define _ISHIKO_PROCESS_TEST_COMMANDLINESPECIFICATIONTESTS_H_

#include <Ishiko/TestFramework/TestFrameworkCore.h>

class CommandLineSpecificationTests : public Ishiko::Tests::TestSequence
{
public:
    CommandLineSpecificationTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
};

#endif
