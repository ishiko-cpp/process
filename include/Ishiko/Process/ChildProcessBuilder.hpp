// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_PROCESS_CHILDPROCESSBUILDER_HPP
#define GUARD_ISHIKO_CPP_PROCESS_CHILDPROCESSBUILDER_HPP

#include "CommandLine.h"
#include "Environment.h"
#include "ChildProcess.hpp"
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
