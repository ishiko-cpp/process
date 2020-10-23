/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "Environment.h"

namespace Ishiko
{
namespace Process
{

Environment::Environment()
{
    m_variables.push_back(nullptr);
}

Environment::~Environment()
{
}

std::vector<char> Environment::toEnvironmentBlock() const
{
    std::vector<char> result;

    result.push_back('\0');

    result.push_back('\0');

    return result;
}

}
}
