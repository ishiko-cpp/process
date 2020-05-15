/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_PROCESS_PROCESSTESTS_PROCESSHANDLETESTS_H_
#define _ISHIKO_TEST_PROCESS_PROCESSTESTS_PROCESSHANDLETESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class ProcessHandleTests : public Ishiko::Tests::TestSequence
{
public:
    ProcessHandleTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
};

#endif
