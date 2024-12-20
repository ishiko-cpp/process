// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "CommandLine.hpp"

namespace Ishiko
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

CommandLine::CommandLine(const char* commandLine)
    : CommandLine(std::string(commandLine))
{
}

CommandLine::CommandLine(const std::string& commandLine)
{
    size_t startPos = 0;
    size_t currentPos = 0;
    while (currentPos < commandLine.size())
    {
        switch (commandLine[currentPos])
        {
        case ' ':
            if (m_executable.empty())
            {
                m_executable = commandLine.substr(startPos, currentPos - startPos);
            }
            else
            {
                m_arguments.emplace_back(commandLine.substr(startPos, currentPos - startPos));
            }
            ++currentPos;
            startPos = currentPos;
            break;

        // TODO: handle quotes and escape sequences

        default:
            break;
        }
        ++currentPos;
    }
    if (startPos != commandLine.size())
    {
        if (m_executable.empty())
        {
            m_executable = commandLine.substr(startPos);
        }
        else
        {
            m_arguments.emplace_back(commandLine.substr(startPos));
        }
    }
}

CommandLine::CommandLine(const char* executable, const std::vector<std::string>& arguments)
    : m_executable(executable), m_arguments(arguments)
{
}

CommandLine::CommandLine(const std::string& executable, const std::vector<std::string>& arguments)
    : m_executable(executable), m_arguments(arguments)
{
}

CommandLine::CommandLine(const boost::filesystem::path& executable, const std::vector<std::string>& arguments)
    : m_executable(executable.string()), m_arguments(arguments)
{
}

void CommandLine::appendArgument(const std::string& argument)
{
    m_arguments.emplace_back(argument);
}

std::string CommandLine::getExecutable(Mode mode) const
{
    std::string result;
    switch (mode)
    {
    case Mode::raw:
        result = m_executable;
        break;

    case Mode::quote_if_needed:
        result = GetQuotedStringIfRequired(m_executable);
        break;
    }
    return result;
}

std::vector<std::string> CommandLine::getArguments(Mode mode) const
{
    std::vector<std::string> result;
    if (mode == Mode::raw)
    {
        result = m_arguments;
    }
    else if (mode == Mode::quote_if_needed)
    {
        result.reserve(m_arguments.size());
        for (const std::string& argument : m_arguments)
        {
            result.emplace_back(GetQuotedStringIfRequired(argument));
        }
    }
    return result;
}

std::string CommandLine::toString(Mode mode) const
{
    std::string result = getExecutable(mode);
    for (const std::string& argument : getArguments(mode))
    {
        result.append(" ");
        result.append(argument);
    }
    return result;
}

}
