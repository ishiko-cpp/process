// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_PROCESS_PROCESSERRORCATEGORY_HPP
#define GUARD_ISHIKO_CPP_PROCESS_PROCESSERRORCATEGORY_HPP

#include <Ishiko/Errors.hpp>

namespace Ishiko
{

class ProcessErrorCategory : public ErrorCategory
{
public:
    enum class Value
    {
        generic = -1
    };

    static const ProcessErrorCategory& Get() noexcept;

    const char* name() const noexcept override;
    const char* message(int ev, char* buffer, size_t len) const noexcept override;

private:
    ProcessErrorCategory() noexcept = default;
};

void Fail(ProcessErrorCategory::Value value, Error& error) noexcept;

}

#endif
