/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_PROCESS_ERRORCATEGORY_H_
#define _ISHIKO_CPP_PROCESS_ERRORCATEGORY_H_

#include <Ishiko/Errors/ErrorCategory.h>
#include <Ishiko/Errors/Error.h>

namespace Ishiko
{
namespace Process
{

class ErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum EErrorValues
    {
        eGeneric = -1
    };

    static const ErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    ErrorCategory() noexcept = default;
};

void Fail(Error& error, ErrorCategory::EErrorValues value) noexcept;

}
}

#endif
