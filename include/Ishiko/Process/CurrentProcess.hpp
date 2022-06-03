/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_PROCESS_CURRENTPROCESS_HPP_
#define _ISHIKO_CPP_PROCESS_CURRENTPROCESS_HPP_

#include <boost/filesystem.hpp>
#include <string>

namespace Ishiko
{

class CurrentProcess
{
public:
    static void RedirectStandardOutputToFile(const boost::filesystem::path& path);
    static void RedirectStandardOutputToFile(const std::string& path);
    static void RedirectStandardOutputToTerminal();
    static void RedirectStandardErrorToFile(const boost::filesystem::path& path);
    static void RedirectStandardErrorToFile(const std::string& path);
    static void RedirectStandardErrorToTerminal();
};

}

#endif
