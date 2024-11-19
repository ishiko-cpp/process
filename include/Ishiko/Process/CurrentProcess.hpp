// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_PROCESS_CURRENTPROCESS_HPP
#define GUARD_ISHIKO_CPP_PROCESS_CURRENTPROCESS_HPP

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
