/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_PROCESSHANDLE_H_
#define _ISHIKO_PROCESS_PROCESSHANDLE_H_

#if defined(__linux__)
#include <sys/types.h>
#elif defined(_WIN32)
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#endif

namespace Ishiko
{
namespace Process
{

class ProcessHandle
{
public:
    ProcessHandle();
#ifdef _WIN32
    ProcessHandle(HANDLE nativeHandle);
#endif
    ProcessHandle(const ProcessHandle& other) = delete;
    ~ProcessHandle();

    ProcessHandle& operator=(const ProcessHandle& other) = delete;

#if defined(__linux__)
    void assign(pid_t pid);
#elif defined(_WIN32)
    void assign(HANDLE nativeHandle);
#endif

    void waitForExit();
    void kill(int exitCode) const;
    int exitCode() const;

private:
#if defined(__linux__)
    pid_t m_pid;
    int m_status;
#elif defined(_WIN32)
    HANDLE m_handle;
#endif
};

}
}

#include "linkoptions.h"

#endif
