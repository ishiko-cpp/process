// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "ProcessErrorCategory.hpp"

using namespace Ishiko;

const ProcessErrorCategory& ProcessErrorCategory::Get() noexcept
{
    static ProcessErrorCategory theCategory;
    return theCategory;
}

const char* ProcessErrorCategory::name() const noexcept
{
    return "Ishiko::ProcessErrorCategory";
}

const char* ProcessErrorCategory::message(int ev, char* buffer, size_t len) const noexcept
{
    switch (static_cast<Value>(ev))
    {
    case Value::generic:
        return "generic error";

    default:
        return "unknown value";
    }
}

void Ishiko::Fail(ProcessErrorCategory::Value value, Error& error) noexcept
{
    error.fail(ProcessErrorCategory::Get(), static_cast<int>(value));
}
