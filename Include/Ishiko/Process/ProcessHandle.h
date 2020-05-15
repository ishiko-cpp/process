/*
    Copyright (c) 2016 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OROTHER DEALINGS
    IN THE SOFTWARE.
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
