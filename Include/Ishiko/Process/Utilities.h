/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_UTILITIES_H_
#define _ISHIKO_PROCESS_UTILITIES_H_

#include "ChildProcess.h"
#include "Environment.h"
#include <Ishiko/Errors/Error.h>
#include <string>

namespace Ishiko
{
namespace Process
{

ChildProcess Spawn(const std::string& commandLine);
ChildProcess Spawn(const std::string& commandLine, Error& error) noexcept;
ChildProcess Spawn(const std::string& commandLine, const Environment& environment);
ChildProcess Spawn(const std::string& commandLine, const Environment& environment, Error& error) noexcept;

}
}

#endif
