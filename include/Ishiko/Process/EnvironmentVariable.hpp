// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_PROCESS_ENVIRONMENTVARIABLE_HPP
#define GUARD_ISHIKO_CPP_PROCESS_ENVIRONMENTVARIABLE_HPP

#include <string>

namespace Ishiko
{
    class EnvironmentVariable
    {
    public:
        explicit EnvironmentVariable(const char* variable);

        const char* variable() const noexcept;
        std::string name() const;
        std::string value() const;

        int compareName(const char* name) const noexcept;

    private:
        const char* m_variable;
    };
}

#endif
