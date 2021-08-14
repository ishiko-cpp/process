/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_PROCESS_ENVIRONMENT_H_
#define _ISHIKO_CPP_PROCESS_ENVIRONMENT_H_

#include "EnvironmentVariable.h"
#include "CurrentEnvironment.h"
#include <vector>

namespace Ishiko
{
namespace Process
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
}

#endif
