/*
    Copyright (c) 2005-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/process/blob/main/LICENSE.txt
*/

#include "CurrentEnvironment.h"
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

namespace Ishiko
{
namespace Process
{

bool CurrentEnvironment::Find(const std::string& name, std::string& value)
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
    _dupenv_s(&v, NULL, name.c_str());
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

std::string CurrentEnvironment::ExpandVariablesInString(const std::string& str, int format)
{
    std::string result;

    size_t lastAddedPos = 0;
    if (format & eDollarAndParentheses)
    {
        size_t beginPos = str.find("$(", lastAddedPos);
        while (beginPos != std::string::npos)
        {
            size_t endPos = str.find(")", beginPos);
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
            beginPos = str.find("$(", beginPos);
        }
    }
    result += str.substr(lastAddedPos);

    return result;
}

}
}
