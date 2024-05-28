/*
    Copyright (c) 2020-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

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
