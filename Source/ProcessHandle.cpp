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

#include "ProcessHandle.h"

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

#ifdef _WIN32
void ProcessHandle::assign(HANDLE nativeHandle)
{
    CloseHandle(m_handle);
    m_handle = nativeHandle;
}
#endif

void ProcessHandle::waitForExit() const
{
#ifdef _WIN32
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
#ifdef _WIN32
    DWORD exitCode;
    GetExitCodeProcess(m_handle, &exitCode);
    return exitCode;
#endif
}

}
}
