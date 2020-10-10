/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_CURRENTPROCESS_H_
#define _ISHIKO_PROCESS_CURRENTPROCESS_H_

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
