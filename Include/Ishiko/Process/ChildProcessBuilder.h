/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_CHILDPROCESSBUILDER_H_
#define _ISHIKO_PROCESS_CHILDPROCESSBUILDER_H_

#include "CommandLine.h"
#include "ChildProcess.h"
#include <Ishiko/Errors/Error.h>
#include <string>

namespace Ishiko
{
namespace Process
{

class ChildProcessBuilder
{
public:
    static void StartProcess(const std::string& commandLine, ChildProcess& handle, Error& error);

    ChildProcessBuilder(const CommandLine& commandLine);

    void start(ChildProcess& handle, Error& error);

    void redirectStandardOutputToFile(const std::string& path);

#ifdef _WIN32
private:
    static HANDLE createInheritableFile(const std::string& path);
#endif


private:
    CommandLine m_commandLine;
    std::string m_standardOutputFilePath;
};

}
}

#include "linkoptions.h"

#endif
