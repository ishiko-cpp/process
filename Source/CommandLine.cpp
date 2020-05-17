/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "CommandLine.h"

namespace Ishiko
{
namespace Process
{

namespace
{

// Checks whether the string has spaces that are not escaped i.e. not enclosed in quotes or prefixed by '\'.
bool HasUnescapedSpaces(const std::string& str)
{
    bool insideQuotes = false;
    for (const char c : str)
    {
        switch (c)
        {
        case '\"':
            insideQuotes = !insideQuotes;
            break;

        case ' ':
            if (!insideQuotes)
            {
                return true;
            }
            break;

        default:
            break;
        }
    }

    return false;
}

// If the given string has unescaped spaces then this function returns a quoted version of the string else it returns
// an unmodified copy of the string.
std::string GetQuotedStringIfRequired(const std::string& str)
{
    if (HasUnescapedSpaces(str))
    {
        std::string result;
        result.reserve(str.size() + 2);
        result.append("\"");
        result.append(str);
        result.append("\"");
        return result;
    }
    else
    {
        return str;
    }
}

}

CommandLine::CommandLine(const char* executable)
    : m_executable(GetQuotedStringIfRequired(executable))
{
}

CommandLine::CommandLine(const std::string& executable)
    : m_executable(GetQuotedStringIfRequired(executable))
{
}

CommandLine::CommandLine(const boost::filesystem::path& executable)
    : m_executable(GetQuotedStringIfRequired(executable.string()))
{
}

CommandLine::CommandLine(const char* executable, const std::vector<std::string>& arguments)
    : m_executable(GetQuotedStringIfRequired(executable))
{
    m_arguments.reserve(arguments.size());
    for (const std::string& argument : arguments)
    {
        m_arguments.emplace_back(GetQuotedStringIfRequired(argument));
    }
}

CommandLine::CommandLine(const std::string& executable, const std::vector<std::string>& arguments)
    : m_executable(GetQuotedStringIfRequired(executable))
{
    m_arguments.reserve(arguments.size());
    for (const std::string& argument : arguments)
    {
        m_arguments.emplace_back(GetQuotedStringIfRequired(argument));
    }
}

CommandLine::CommandLine(const boost::filesystem::path& executable, const std::vector<std::string>& arguments)
    : m_executable(GetQuotedStringIfRequired(executable.string()))
{
    m_arguments.reserve(arguments.size());
    for (const std::string& argument : arguments)
    {
        m_arguments.emplace_back(GetQuotedStringIfRequired(argument));
    }
}

const std::string& CommandLine::executable() const
{
    return m_executable;
}

const std::vector<std::string>& CommandLine::arguments() const
{
    return m_arguments;
}

std::string CommandLine::toString() const
{
    std::string result = m_executable;
    for (const std::string& argument : m_arguments)
    {
        result.append(" ");
        result.append(argument);
    }
    return result;
}

}
}
