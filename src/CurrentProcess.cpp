// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "CurrentProcess.hpp"
#include <Ishiko/BasePlatform.hpp>

using namespace Ishiko;

void CurrentProcess::RedirectStandardOutputToFile(const boost::filesystem::path& path)
{
    RedirectStandardOutputToFile(path.string());
}

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
    RedirectStandardOutputToFile(std::string("/dev/tty"));
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    RedirectStandardOutputToFile(std::string("CON"));
#else
    #error Unsupported OS
#endif
}

void CurrentProcess::RedirectStandardErrorToFile(const boost::filesystem::path& path)
{
    RedirectStandardErrorToFile(path.string());
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
    RedirectStandardErrorToFile(std::string("/dev/tty"));
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    RedirectStandardErrorToFile(std::string("CON"));
#else
    #error Unsupported OS
#endif
}
