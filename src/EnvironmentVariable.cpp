// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "EnvironmentVariable.hpp"
#include <cstring>

using namespace Ishiko;

EnvironmentVariable::EnvironmentVariable(const char* variable)
    : m_variable(variable)
{
}

const char* EnvironmentVariable::variable() const noexcept
{
    return m_variable;
}

std::string EnvironmentVariable::name() const
{
    const char* equal = strchr(m_variable, '=');
    return std::string(m_variable, equal - m_variable);
}

std::string EnvironmentVariable::value() const
{
    const char* equal = strchr(m_variable, '=');
    return std::string(equal + 1);
}

int EnvironmentVariable::compareName(const char* name) const noexcept
{
    if (m_variable == nullptr)
    {
        return 1;
    }

    size_t i = 0;
    while ((name[i] != 0) && (m_variable[i] != 0) && (name[i] == m_variable[i]))
    {
        ++i;
    }
    if (m_variable[i] == '=')
    {
        if (name[i] == 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else if (m_variable[i] < name[i])
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
