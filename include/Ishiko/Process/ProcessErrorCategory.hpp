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

class ProcessErrorCategory : public ErrorCategory
{
public:
    enum class Value
    {
        generic = -1
    };

    static const ProcessErrorCategory& Get() noexcept;

    const char* name() const noexcept override;
    std::ostream& streamOut(int value, std::ostream& os) const override;

private:
    ProcessErrorCategory() noexcept = default;
};

void Fail(ProcessErrorCategory::Value value, Error& error) noexcept;

}

#endif
