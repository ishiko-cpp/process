/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ChildProcess.h"
#ifdef __linux__
#include <sys/wait.h>
#endif

namespace Ishiko
{
namespace Process
{

ChildProcess::ChildProcess()
#ifdef _WIN32
    : m_handle(INVALID_HANDLE_VALUE)
#endif
{
}

#ifdef _WIN32
ChildProcess::ChildProcess(HANDLE nativeHandle)
    : m_handle(nativeHandle)
{
}
#endif

#if defined(__linux__)
ChildProcess::ChildProcess(ChildProcess&& other) noexcept
    : m_pid(other.m_pid), m_status(other.m_status)
{
}
#elif defined(_WIN32)
ChildProcess::ChildProcess(ChildProcess&& other) noexcept
    : m_handle(other.m_handle)
{
    other.m_handle = INVALID_HANDLE_VALUE;
}
#endif

ChildProcess::~ChildProcess()
{
#ifdef _WIN32
    if (m_handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_handle);
    }
#endif
}

#if defined(__linux__)
void ChildProcess::assign(pid_t pid)
{
    m_pid = pid;
}
#elif defined(_WIN32)
void ChildProcess::assign(HANDLE nativeHandle)
{
    CloseHandle(m_handle);
    m_handle = nativeHandle;
}
#endif

void ChildProcess::waitForExit()
{
#if defined(__linux__)
    waitpid(m_pid, &m_status, 0);
#elif defined(_WIN32)
    WaitForSingleObject(m_handle, INFINITE);
#endif
}

void ChildProcess::kill(int exitCode) const
{
#ifdef _WIN32
    TerminateProcess(m_handle, exitCode);
#endif
}

int ChildProcess::exitCode() const
{
#if defined(__linux__)
    return m_status;
#elif defined(_WIN32)
    DWORD exitCode;
    GetExitCodeProcess(m_handle, &exitCode);
    return exitCode;
#endif
}

}
}
