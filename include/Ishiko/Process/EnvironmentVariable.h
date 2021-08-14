/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_PROCESS_ENVIRONMENTVARIABLE_H_
#define _ISHIKO_CPP_PROCESS_ENVIRONMENTVARIABLE_H_

#include <string>

namespace Ishiko
{
namespace Process
{

class EnvironmentVariable
{
public:
    explicit EnvironmentVariable(const char* variable);

    std::string name() const;
    std::string value() const;

    const char* m_variable;
};

}
}

#endif
