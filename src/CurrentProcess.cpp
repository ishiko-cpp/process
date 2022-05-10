/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "CurrentProcess.h"
#include <Ishiko/BasePlatform.h>

using namespace Ishiko;

void CurrentProcess::RedirectStandardOutputToFile(const std::string& path)
{
#if ISHIKO_COMPILER == ISHIKO_COMPILER_GCC
    freopen(path.c_str(), "a", stdout);
#elif ISHIKO_COMPILER == ISHIKO_COMPILER_MSVC
    FILE* dummy;
    freopen_s(&dummy, path.c_str(), "a", stdout);
#else
    #error Unsupported or unrecognized compiler
#endif
}

void CurrentProcess::RedirectStandardOutputToTerminal()
{
#if ISHIKO_OS == ISHIKO_OS_LINUX
    RedirectStandardOutputToFile("/dev/tty");
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    RedirectStandardOutputToFile("CON");
#else
    #error Unsupported OS
#endif
}

void CurrentProcess::RedirectStandardErrorToFile(const std::string& path)
{
#if ISHIKO_COMPILER == ISHIKO_COMPILER_GCC
    freopen(path.c_str(), "a", stderr);
#elif ISHIKO_COMPILER == ISHIKO_COMPILER_MSVC
    FILE* dummy;
    freopen_s(&dummy, path.c_str(), "a", stderr);
#else
    #error Unsupported or unrecognized compiler
#endif
}

void CurrentProcess::RedirectStandardErrorToTerminal()
{
#if ISHIKO_OS == ISHIKO_OS_LINUX
    RedirectStandardErrorToFile("/dev/tty");
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    RedirectStandardErrorToFile("CON");
#else
    #error Unsupported OS
#endif
}
