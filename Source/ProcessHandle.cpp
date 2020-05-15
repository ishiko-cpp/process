/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ProcessHandle.h"
#ifdef __linux__
#include <sys/wait.h>
#endif

namespace Ishiko
{
namespace Process
{

ProcessHandle::ProcessHandle()
#ifdef _WIN32
    : m_handle(GetCurrentProcess())
#endif
{
}

#ifdef _WIN32
ProcessHandle::ProcessHandle(HANDLE nativeHandle)
    : m_handle(nativeHandle)
{
}
#endif

ProcessHandle::~ProcessHandle()
{
#ifdef _WIN32
    CloseHandle(m_handle);
#endif
}

#if defined(__linux__)
void ProcessHandle::assign(pid_t pid)
{
    m_pid = pid;
}
#elif defined(_WIN32)
void ProcessHandle::assign(HANDLE nativeHandle)
{
    CloseHandle(m_handle);
    m_handle = nativeHandle;
}
#endif

void ProcessHandle::waitForExit()
{
#if defined(__linux__)
    waitpid(m_pid, &m_status, 0);
#elif defined(_WIN32)
    WaitForSingleObject(m_handle, INFINITE);
#endif
}

void ProcessHandle::kill(int exitCode) const
{
#ifdef _WIN32
    TerminateProcess(m_handle, exitCode);
#endif
}

int ProcessHandle::exitCode() const
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
