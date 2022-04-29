/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_PROCESS_CHILDPROCESSBUILDER_H_
#define _ISHIKO_CPP_PROCESS_CHILDPROCESSBUILDER_H_

#include "CommandLine.h"
#include "Environment.h"
#include "ChildProcess.h"
#include <boost/optional/optional.hpp>
#include <Ishiko/Errors.hpp>
#include <string>

namespace Ishiko
{

class ChildProcessBuilder
{
public:
    ChildProcessBuilder(const std::string& commandLine);
    ChildProcessBuilder(const CommandLine& commandLine);
    ChildProcessBuilder(const CommandLine& commandLine, const Environment& environment);

    ChildProcess start();
    ChildProcess start(Error& error) noexcept;

    void redirectStandardOutputToFile(const std::string& path);

private:
    CommandLine m_commandLine;
    boost::optional<Environment> m_environment;
    std::string m_standardOutputFilePath;
};

}

#endif
