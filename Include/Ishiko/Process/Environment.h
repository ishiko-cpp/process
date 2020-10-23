/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_ENVIRONMENT_H_
#define _ISHIKO_PROCESS_ENVIRONMENT_H_

#include <vector>

namespace Ishiko
{
namespace Process
{

class Environment
{
public:
    Environment();
    ~Environment();
    
    std::vector<char> toEnvironmentBlock() const;

    std::vector<char*> m_variables;
};

}
}

#endif
