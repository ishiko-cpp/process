// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_PROCESS_ENVIRONMENT_HPP
#define GUARD_ISHIKO_CPP_PROCESS_ENVIRONMENT_HPP

#include "EnvironmentVariable.hpp"
#include "CurrentEnvironment.hpp"
#include <vector>

namespace Ishiko
{

class Environment
{
public:
    Environment();
    Environment(const CurrentEnvironment& env);
    Environment(const Environment& other);
    ~Environment();

    size_t size() const;
    const EnvironmentVariable& operator[](size_t pos) const noexcept;

    std::vector<EnvironmentVariable>::const_iterator begin() const noexcept;
    std::vector<EnvironmentVariable>::const_iterator end() const noexcept;

    bool find(const std::string& name, std::string& value) const;
    void set(const char* name, const char* value);
    
    char** toEnvironmentArray();
    std::vector<char> toEnvironmentBlock() const;

private:
    std::vector<EnvironmentVariable> m_variables;
};

}

#endif
