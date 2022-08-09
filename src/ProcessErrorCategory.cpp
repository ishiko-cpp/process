/*
    Copyright (c) 2020-2022 Xavier Leclercq
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

std::ostream& ProcessErrorCategory::streamOut(int value, std::ostream& os) const
{
    switch (static_cast<Value>(value))
    {
    case Value::generic:
        os << "generic error";
        break;

    default:
        os << "unknown value";
        break;
    }
    return os;
}

void Ishiko::Fail(ProcessErrorCategory::Value value, Error& error) noexcept
{
    error.fail(ProcessErrorCategory::Get(), static_cast<int>(value));
}
