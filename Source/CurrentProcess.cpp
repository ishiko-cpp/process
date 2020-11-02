/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "CurrentProcess.h"
#include <Ishiko/Platform/Compilers.h>
#include <Ishiko/Platform/OS.h>

namespace Ishiko
{
namespace Process
{

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

}
}
