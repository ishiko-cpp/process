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

void Ishiko::Fail(ProcessErrorCategory::EErrorValues value, Error& error) noexcept
{
    error.fail(ProcessErrorCategory::Get(), value);
}
