/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_COMMANDLINE_H_
#define _ISHIKO_PROCESS_COMMANDLINE_H_

#include <string>

namespace Ishiko
{
namespace Process
{

class CommandLine
{
public:
    CommandLine(const char* executable);
    CommandLine(const std::string& executable);

    const std::string& executable() const;

private:
    std::string m_executable;
};

}
}

#endif
