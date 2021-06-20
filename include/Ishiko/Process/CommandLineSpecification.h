/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_COMMANDLINESPECIFICATION_H_
#define _ISHIKO_PROCESS_COMMANDLINESPECIFICATION_H_

#include <map>
#include <string>

namespace Ishiko
{
namespace Process
{

class CommandLineSpecification
{
public:
    class OptionDetails
    {
    };

    void addNamedOption(const std::string& name);

    bool find(const std::string& name, OptionDetails& details) const;

private:
    std::map<std::string, OptionDetails> m_options;
};

}
}

#endif
