/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ChildProcess.h"
#include "ChildProcessBuilder.h"
#if ISHIKO_OS == ISHIKO_OS_LINUX
#include <sys/wait.h>
#endif

namespace Ishiko
{
namespace Process
{

ChildProcess ChildProcess::Spawn(const std::string& commandLine)
{
    ChildProcessBuilder builder{CommandLine(commandLine)};
    return builder.start();
}

ChildProcess ChildProcess::Spawn(const std::string& commandLine, Error& error) noexcept
{
    ChildProcessBuilder builder{CommandLine(commandLine)};
    return builder.start(error);
}

ChildProcess ChildProcess::Spawn(const std::string& commandLine, const Environment& environment)
{
    ChildProcessBuilder builder{CommandLine(commandLine), environment};
    return builder.start();
}

ChildProcess ChildProcess::Spawn(const std::string& commandLine, const Environment& environment, Error& error) noexcept
{
    ChildProcessBuilder builder{CommandLine(commandLine), environment};
    return builder.start(error);
}

ChildProcess::ChildProcess()
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
    : m_handle(INVALID_HANDLE_VALUE)
#endif
{
}

#if ISHIKO_OS == ISHIKO_OS_LINUX
ChildProcess::ChildProcess(pid_t pid)
    : m_pid(pid)
{
}
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
ChildProcess::ChildProcess(HANDLE nativeHandle)
    : m_handle(nativeHandle)
{
}
#else
    #error Unsupported or unrecognized OS
#endif

#if ISHIKO_OS == ISHIKO_OS_LINUX
ChildProcess::ChildProcess(ChildProcess&& other) noexcept
    : m_pid(other.m_pid), m_status(other.m_status)
{
}
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
ChildProcess::ChildProcess(ChildProcess&& other) noexcept
    : m_handle(other.m_handle)
{
    other.m_handle = INVALID_HANDLE_VALUE;
}
#else
    #error Unsupported or unrecognized OS
#endif

ChildProcess::~ChildProcess()
{
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
    if (m_handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_handle);
    }
#endif
}

#if ISHIKO_OS == ISHIKO_OS_LINUX
ChildProcess& ChildProcess::operator=(ChildProcess&& other) noexcept
{
    m_pid = other.m_pid;
    m_status = other.m_status;
    return *this;
}
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
ChildProcess& ChildProcess::operator=(ChildProcess&& other) noexcept
{
    if (this != &other)
    {
        m_handle = other.m_handle;
        other.m_handle = INVALID_HANDLE_VALUE;
    }
    return *this;
}
#else
    #error Unsupported or unrecognized OS
#endif

#if ISHIKO_OS == ISHIKO_OS_LINUX
void ChildProcess::assign(pid_t pid)
{
    m_pid = pid;
}
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
void ChildProcess::assign(HANDLE nativeHandle)
{
    CloseHandle(m_handle);
    m_handle = nativeHandle;
}
#else
    #error Unsupported or unrecognized OS
#endif

void ChildProcess::waitForExit()
{
#if ISHIKO_OS == ISHIKO_OS_LINUX
    waitpid(m_pid, &m_status, 0);
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    WaitForSingleObject(m_handle, INFINITE);
#else
    #error Unsupported or unrecognized OS
#endif
}

// TODO: exit code doesn't work on Linux
void ChildProcess::kill(int exitCode) const
{
#if ISHIKO_OS == ISHIKO_OS_LINUX
    ::kill(m_pid, SIGKILL);
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    TerminateProcess(m_handle, exitCode);
#else
    #error Unsupported or unrecognized OS
#endif
}

int ChildProcess::exitCode() const
{
#if ISHIKO_OS == ISHIKO_OS_LINUX
    // TODO: what if not exited?
    return WEXITSTATUS(m_status);
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    DWORD exitCode;
    GetExitCodeProcess(m_handle, &exitCode);
    return exitCode;
#else
    #error Unsupported or unrecognized OS
#endif
}

}
}
