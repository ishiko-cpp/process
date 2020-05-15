/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_COMMANDLINETESTS_H_
#define _ISHIKO_TEST_COMMANDLINETESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class CommandLineTests : public Ishiko::Tests::TestSequence
{
public:
    CommandLineTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);
};

#endif
