/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
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

void Fail(Error& error, ErrorCategory::EErrorValues value) noexcept
{
    error.fail(value, ErrorCategory::Get());
}

}
}
