// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_PROCESS_COMMANDLINE_H
#define GUARD_ISHIKO_CPP_PROCESS_COMMANDLINE_H

#include <boost/filesystem/path.hpp>
#include <string>
#include <vector>

namespace Ishiko
{

/// A class that represent the command line used to launch an executable.
/**
    A command line is comprised of an executable and zero or more arguments.
*/
class CommandLine
{
public:
    enum class Mode
    {
        raw,
        quote_if_needed
    };

    /// Creates a new CommandLine instance.
    /**
        @param commandLine The command line.
    */
    explicit CommandLine(const char* commandLine);

    /// Creates a new CommandLine instance.
    /**
        @param commandLine The command line.
    */
    explicit CommandLine(const std::string& commandLine);

    /// Creates a new CommandLine instance.
    /**
        @param executable The executable.
        @param arguments The command line arguments.
    */
    CommandLine(const char* executable, const std::vector<std::string>& arguments);

    /// Creates a new CommandLine instance.
    /**
        @param executable The executable.
        @param arguments The command line arguments.
    */
    CommandLine(const std::string& executable, const std::vector<std::string>& arguments);

    /// Creates a new CommandLine instance.
    /**
        @param executable The executable.
        @param arguments The command line arguments.
    */
    CommandLine(const boost::filesystem::path& executable, const std::vector<std::string>& arguments);

    void appendArgument(const std::string& argument);

    std::string getExecutable(Mode mode) const;
    std::vector<std::string> getArguments(Mode mode) const;

    std::string toString(Mode mode) const;

private:
    std::string m_executable;
    std::vector<std::string> m_arguments;
};

}

#endif
