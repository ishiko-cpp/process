/*
    Copyright (c) 2005-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_CURRENTENVIRONMENT_H_
#define _ISHIKO_PROCESS_CURRENTENVIRONMENT_H_

#include <map>
#include <string>

namespace Ishiko
{
namespace Process
{

class CurrentEnvironment
{
public:
    enum EReferenceFormat
    {
        eDollarAndParentheses = 0x01
    };

public:
    static bool Find(const std::string& name, std::string& value);
    static std::map<std::string, std::string> ToMap();
    static void Set(const std::string& name, const std::string& value);

    static std::string ExpandVariablesInString(const std::string& str, int format);
};

}
}

#include "linkoptions.h"

#endif
