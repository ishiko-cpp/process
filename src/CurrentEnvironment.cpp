/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "CurrentEnvironment.hpp"
#include <Ishiko/BasePlatform.h>
#include <cstring>
#include <stdlib.h>

#if ISHIKO_OS == ISHIKO_OS_LINUX
extern char** environ;
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
// There seems to be an error with the definition of GetEnvironmentStringsA so we undefine UNICODE so that we can use
// GetEnvironmentStrings
#undef UNICODE
#include <Windows.h>
#endif

using namespace Ishiko;

CurrentEnvironment::InterpolatedStringCallbacks::InterpolatedStringCallbacks(bool allowMissing)
    : m_allowMissing(allowMissing)
{
}

void CurrentEnvironment::InterpolatedStringCallbacks::expand(boost::string_view variable, std::string& result,
    Error& error) const
{
    std::string value;
    bool found = Find(variable, value);
    if (found)
    {
        result.append(value);
    }
    else if (!m_allowMissing)
    {
        Fail(error, TextErrorCategory::Value::generic);
    }
}

bool CurrentEnvironment::Find(const char* name, std::string& value)
{
    return Find(boost::string_view(name), value);
}

bool CurrentEnvironment::Find(const std::string& name, std::string& value)
{
    return Find(boost::string_view(name.c_str(), name.size()), value);
}

bool CurrentEnvironment::Find(boost::string_view name, std::string& value)
{
#if ISHIKO_COMPILER == ISHIKO_COMPILER_GCC
    char* v = getenv(name.c_str());
    if (v == NULL)
    {
        return false;
    }
    else
    {
        value = v;
        return true;
    }
#elif ISHIKO_COMPILER == ISHIKO_COMPILER_MSVC
    char* v = NULL;
    _dupenv_s(&v, NULL, name.data());
    if (v == NULL)
    {
        return false;
    }
    else
    {
        value = v;
        free(v);
        return true;
    }
#else
    #error Unsupported or unrecognized compiler
#endif
}

std::map<std::string, std::string> CurrentEnvironment::ToMap()
{
    std::map<std::string, std::string> result;

#if ISHIKO_OS == ISHIKO_OS_LINUX
    for (char** p = environ; *p != nullptr; ++p)
    {
        char* eq = strchr(*p, '=');
        result.emplace(std::string(*p, eq - *p), std::string(eq + 1));
    }
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    char* environment = GetEnvironmentStrings();
    for (char* p = environment; *p != '\0'; ++p)
    {
        char* eq = strchr(p, '=');
        result.emplace(std::string(p, eq - p), std::string(eq + 1));
        do
        {
            ++p;
        } while (*p != '\0');
    }
    FreeEnvironmentStrings(environment);
#else
    #error Unsupported or unrecognized OS
#endif

    return result;
}

void CurrentEnvironment::Set(const std::string& name, const std::string& value)
{
#if ISHIKO_OS == ISHIKO_OS_LINUX
    setenv(name.c_str(), value.c_str(), 1);
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    _putenv_s(name.c_str(), value.c_str());
#else
    #error Unsupported or unrecognized OS
#endif
}

std::string CurrentEnvironment::ExpandVariablesInString(const std::string& str, SubstitutionFormat format)
{
    std::string result;

    size_t lastAddedPos = 0;
    const char* startPattern;
    const char* endPattern;
    switch (format)
    {
    case SubstitutionFormat::DollarAndCurlyBrackets:
        startPattern = "${";
        endPattern = "}";
        break;

    case SubstitutionFormat::DollarAndRoundBrackets:
        startPattern = "$(";
        endPattern = ")";
        break;

    default:
        // TODO: error if format unrecognized
        startPattern = "";
        endPattern = "";
        break;
    }
    
    size_t beginPos = str.find(startPattern, lastAddedPos);
    while (beginPos != std::string::npos)
    {
        size_t endPos = str.find(endPattern, beginPos);
        if (endPos != std::string::npos)
        {
            std::string name = str.substr(beginPos + 2, endPos - beginPos - 2);
            std::string value;
            bool found = Find(name, value);
            if (found)
            {
                result += str.substr(lastAddedPos, beginPos - lastAddedPos);
                result += value;
                beginPos = lastAddedPos = endPos + 1;
            }
            else
            {
                beginPos += 2;
            }
        }
        else
        {
            break;
        }
        beginPos = str.find(startPattern, beginPos);
    }
    
    result += str.substr(lastAddedPos);

    return result;
}
