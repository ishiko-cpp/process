/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_CHILDPROCESSBUILDER_H_
#define _ISHIKO_PROCESS_CHILDPROCESSBUILDER_H_

#include "CommandLine.h"
#include "Environment.h"
#include "ChildProcess.h"
#include <Ishiko/Errors/Error.h>
#include <boost/optional/optional.hpp>
#include <string>

namespace Ishiko
{
namespace Process
{

class ChildProcessBuilder
{
public:
    static ChildProcess StartProcess(const std::string& commandLine);
    static ChildProcess StartProcess(const std::string& commandLine, Error& error) noexcept;

    ChildProcessBuilder(const std::string& commandLine);
    ChildProcessBuilder(const CommandLine& commandLine);
    ChildProcessBuilder(const CommandLine& commandLine, const Environment& environment);

    ChildProcess start();
    ChildProcess start(Error& error) noexcept;

    void redirectStandardOutputToFile(const std::string& path);

#ifdef _WIN32
private:
    static HANDLE createInheritableFile(const std::string& path);
#endif

private:
    CommandLine m_commandLine;
    boost::optional<Environment> m_environment;
    std::string m_standardOutputFilePath;
};

}
}

#include "linkoptions.h"

#endif
