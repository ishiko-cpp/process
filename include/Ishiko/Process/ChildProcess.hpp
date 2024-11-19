// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_PROCESS_CHILDPROCESS_HPP
#define GUARD_ISHIKO_CPP_PROCESS_CHILDPROCESS_HPP

#include "Environment.hpp"
#include <Ishiko/BasePlatform.hpp>
#include <Ishiko/Errors.hpp>

#if ISHIKO_OS == ISHIKO_OS_LINUX
    #include <sys/types.h>
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    #define WIN32_LEAN_AND_MEAN 
    #include <Windows.h>
#endif

namespace Ishiko
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

#endif
