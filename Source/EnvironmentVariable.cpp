/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "EnvironmentVariable.h"
#include <cstring>

namespace Ishiko
{
namespace Process
{

EnvironmentVariable::EnvironmentVariable(char* variable)
    : m_variable(variable)
{
}

std::string EnvironmentVariable::name() const
{
    char* equal = strchr(m_variable, '=');
    return std::string(m_variable, equal - m_variable);
}

std::string EnvironmentVariable::value() const
{
    char* equal = strchr(m_variable, '=');
    return std::string(equal + 1);
}

}
}
