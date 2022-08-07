/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_PROCESS_PROCESSERRORCATEGORY_HPP
#define GUARD_ISHIKO_CPP_PROCESS_PROCESSERRORCATEGORY_HPP

#include <Ishiko/Errors.hpp>

namespace Ishiko
{

class ProcessErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum EErrorValues
    {
        eGeneric = -1
    };

    static const ProcessErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    ProcessErrorCategory() noexcept = default;
};

void Fail(ProcessErrorCategory::EErrorValues value, Error& error) noexcept;

}

#endif
