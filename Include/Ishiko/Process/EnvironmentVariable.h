/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_ENVIRONMENTVARIABLE_H_
#define _ISHIKO_PROCESS_ENVIRONMENTVARIABLE_H_

namespace Ishiko
{
namespace Process
{

class EnvironmentVariable
{
public:
    explicit EnvironmentVariable(char* variable);

    char* m_variable;
};

}
}

#endif
