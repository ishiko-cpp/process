/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_COMMANDLINE_H_
#define _ISHIKO_PROCESS_COMMANDLINE_H_

#include <boost/filesystem/path.hpp>
#include <string>
#include <vector>

namespace Ishiko
{
namespace Process
{

/// A class that represent the command line used to launch an executable.
/**
    A command line is comprised of an executable and zero or more arguments.
*/
class CommandLine
{
public:
    enum EMode
    {
        eRaw,
        eQuoteIfNeeded
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

    std::string getExecutable(EMode mode) const;
    std::vector<std::string> getArguments(EMode mode) const;

    std::string toString(EMode mode) const;

private:
    std::string m_executable;
    std::vector<std::string> m_arguments;
};

}
}

#endif
