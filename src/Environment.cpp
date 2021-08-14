/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "Environment.h"
#include <Ishiko/Text/CString.h>
#include <string>
#include <cstring>

namespace Ishiko
{
namespace Process
{

Environment::Environment()
{
    m_variables.push_back(EnvironmentVariable(nullptr));
}

Environment::Environment(const CurrentEnvironment& env)
{
    std::map<std::string, std::string> variables = env.ToMap();
    m_variables.reserve(variables.size());
    for (const auto& variable : variables)
    {
        char* entry = new char[variable.first.size() + variable.second.size() + 2];
        memcpy(entry, variable.first.c_str(), variable.first.size());
        entry[variable.first.size()] = '=';
        memcpy(entry + variable.first.size() + 1, variable.second.c_str(), variable.second.size() + 1);
        m_variables.push_back(EnvironmentVariable(entry));
    }
}

Environment::Environment(const Environment& other)
{
    m_variables.reserve(other.m_variables.size());
    for (size_t i = 0; i < other.m_variables.size() - 1; ++i)
    {
        m_variables.push_back(EnvironmentVariable(Text::CString::Duplicate(other.m_variables[i].m_variable)));
    }
    m_variables.push_back(EnvironmentVariable(nullptr));
}

Environment::~Environment()
{
    for (const EnvironmentVariable& entry : m_variables)
    {
        delete[] entry.m_variable;
    }
}

size_t Environment::size() const
{
    return (m_variables.size() - 1);
}

const EnvironmentVariable& Environment::operator[](size_t pos) const noexcept
{
    return m_variables[pos];
}

std::vector<EnvironmentVariable>::const_iterator Environment::begin() const noexcept
{
    return m_variables.begin();
}

std::vector<EnvironmentVariable>::const_iterator Environment::end() const noexcept
{
    return (m_variables.end() - 1);
}

bool Environment::find(const std::string& name, std::string& value) const
{
    for (const EnvironmentVariable& entry : m_variables)
    {
        if ((entry.m_variable != nullptr) && (memcmp(entry.m_variable, name.c_str(), name.size()) == 0))
        {
            if (entry.m_variable[name.size()] == '=')
            {
                value = entry.m_variable + name.size() + 1;
                return true;
            }
        }
    }
    return false;
}

void Environment::set(const char* name, const char* value)
{
    std::string entry = name;
    entry += "=";
    entry += value;
    EnvironmentVariable newVariable(Text::CString::Duplicate(entry.c_str()));

    size_t i = 0;
    while ((i < (m_variables.size() - 1)) && (strcmp(m_variables[i].m_variable, newVariable.m_variable) < 0))
    {
        ++i;
    }
    
    if ((m_variables[i].m_variable != nullptr) && (m_variables[i].name() == newVariable.name()))
    {
        delete[] m_variables[i].m_variable;
        m_variables[i] = newVariable;
    }
    else
    {
        m_variables.insert(m_variables.begin() + i, newVariable);
    }
}

char** Environment::toEnvironmentArray()
{
    return (char**)m_variables.data();
}

std::vector<char> Environment::toEnvironmentBlock() const
{
    std::vector<char> result;

    if (m_variables.size() == 1)
    {
        result.push_back('\0');
    }
    else
    {
        for (size_t i = 0; i < (m_variables.size() - 1); ++i)
        {
            const char* entry = m_variables[i].m_variable;
            result.insert(result.end(), entry, entry + strlen(entry) + 1);
        }
    }

    result.push_back('\0');

    return result;
}

}
}
