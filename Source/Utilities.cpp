/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "Utilities.h"
#include "ChildProcessBuilder.h"

namespace Ishiko
{
namespace Process
{

ChildProcess Spawn(const std::string& commandLine)
{
    ChildProcessBuilder builder{CommandLine(commandLine)};
    return builder.start();
}

ChildProcess Spawn(const std::string& commandLine, Error& error) noexcept
{
    ChildProcessBuilder builder{CommandLine(commandLine)};
    return builder.start(error);
}

}
}
