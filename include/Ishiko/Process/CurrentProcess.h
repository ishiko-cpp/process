/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_PROCESS_CURRENTPROCESS_H_
#define _ISHIKO_CPP_PROCESS_CURRENTPROCESS_H_

#include <string>

namespace Ishiko
{
namespace Process
{

class CurrentProcess
{
public:
    static void RedirectStandardOutputToFile(const std::string& path);
    static void RedirectStandardOutputToTerminal();
};

}
}

#endif
