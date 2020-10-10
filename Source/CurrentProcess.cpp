/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "CurrentProcess.h"

namespace Ishiko
{
namespace Process
{

void CurrentProcess::RedirectStandardOutputToFile(const std::string& path)
{
    freopen(path.c_str(), "a", stdout);
}

void CurrentProcess::RedirectStandardOutputToTerminal()
{
#ifdef WIN32
    RedirectStandardOutputToFile("CON");
#else
    RedirectStandardOutputToFile("/dev/tty");
#endif
}

}
}
