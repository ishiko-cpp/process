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

CommandLine::CommandLine(const char* executable)
    : m_executable(executable)
{
}

CommandLine::CommandLine(const std::string& executable)
    : m_executable(executable)
{
}

const std::string& CommandLine::executable() const
{
    return m_executable;
}

}
}
