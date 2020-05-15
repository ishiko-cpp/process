/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
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
