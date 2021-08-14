/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "ErrorCategory.h"

namespace Ishiko
{
namespace Process
{

const ErrorCategory& ErrorCategory::Get() noexcept
{
    static ErrorCategory theCategory;
    return theCategory;
}

const char* ErrorCategory::name() const noexcept
{
    return "Ishiko::Process::ErrorCategory";
}

void Fail(Error& error, ErrorCategory::EErrorValues value) noexcept
{
    error.fail(value, ErrorCategory::Get());
}

}
}
