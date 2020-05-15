/*
    Copyright (c) 2016-2020 Xavier Leclercq

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

#ifndef _ISHIKO_PROCESS_CHILDPROCESSBUILDER_H_
#define _ISHIKO_PROCESS_CHILDPROCESSBUILDER_H_

#include "ProcessHandle.h"
#include <string>

namespace Ishiko
{
namespace Process
{

class ChildProcessBuilder
{
public:
    static int StartProcess(const std::string& commandLine, ProcessHandle& handle);

    ChildProcessBuilder(const std::string& commandLine);

    int start(ProcessHandle& handle);

    void redirectStandardOutputToFile(const std::string& path);

#ifdef _WIN32
private:
    static HANDLE createInheritableFile(const std::string& path);
#endif


private:
    std::string m_commandLine;
    std::string m_standardOutputFilePath;
};

}
}

#include "linkoptions.h"

#endif
