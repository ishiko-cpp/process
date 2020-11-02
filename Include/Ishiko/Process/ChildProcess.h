/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_CHILDPROCESS_H_
#define _ISHIKO_PROCESS_CHILDPROCESS_H_

#include "Environment.h"
#include <Ishiko/Errors.h>
#include <Ishiko/Platform/OS.h>
#if ISHIKO_OS == ISHIKO_OS_LINUX
#include <sys/types.h>
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#endif

namespace Ishiko
{
namespace Process
{

class ChildProcess
{
public:
    static ChildProcess Spawn(const std::string& commandLine);
    static ChildProcess Spawn(const std::string& commandLine, Error& error) noexcept;
    static ChildProcess Spawn(const std::string& commandLine, const Environment& environment);
    static ChildProcess Spawn(const std::string& commandLine, const Environment& environment, Error& error) noexcept;

    ChildProcess();
#if ISHIKO_OS == ISHIKO_OS_LINUX
    ChildProcess(pid_t pid);
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    ChildProcess(HANDLE nativeHandle);
#else
    #error Unsupported or unrecognized OS
#endif
    ChildProcess(const ChildProcess& other) = delete;
    ChildProcess(ChildProcess&& other) noexcept;
    ~ChildProcess();

    ChildProcess& operator=(const ChildProcess& other) = delete;
    ChildProcess& operator=(ChildProcess&& other) noexcept;

#if ISHIKO_OS == ISHIKO_OS_LINUX
    void assign(pid_t pid);
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    void assign(HANDLE nativeHandle);
#else
    #error Unsupported or unrecognized OS
#endif

    void waitForExit();
    void kill(int exitCode) const;
    int exitCode() const;

private:
#if ISHIKO_OS == ISHIKO_OS_LINUX
    pid_t m_pid;
    int m_status;
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    HANDLE m_handle;
#else
    #error Unsupported or unrecognized OS
#endif
};

}
}

#include "linkoptions.h"

#endif
