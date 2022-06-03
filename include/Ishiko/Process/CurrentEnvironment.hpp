/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_PROCESS_CURRENTENVIRONMENT_HPP_
#define _ISHIKO_CPP_PROCESS_CURRENTENVIRONMENT_HPP_

#include <boost/utility/string_view.hpp>
#include <Ishiko/Text.hpp>
#include <map>
#include <string>

namespace Ishiko
{

class CurrentEnvironment
{
public:
    enum class SubstitutionFormat
    {
        DollarAndCurlyBrackets = 0x01,
        DollarAndRoundBrackets = 0x02
    };

    class InterpolatedStringCallbacks : public InterpolatedString::Callbacks
    {
    public:
        InterpolatedStringCallbacks(bool allowMissing);

        void expand(boost::string_view variable, std::string& result, Error& error) const override;

    private:
        bool m_allowMissing;
    };

public:
    static bool Find(const char* name, std::string& value);
    static bool Find(const std::string& name, std::string& value);
    static bool Find(boost::string_view name, std::string& value);
    static std::map<std::string, std::string> ToMap();
    static void Set(const std::string& name, const std::string& value);

    static std::string Expand(const InterpolatedString& str, bool allowMissing, Error& error);
    static std::string ExpandVariablesInString(const std::string& str, SubstitutionFormat format);
};

}

#endif
