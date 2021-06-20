/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#if defined(_WIN32)
#undef UNICODE
#include <Windows.h>
#endif
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "argc: " << argc << std::endl;
    for (int i = 0; i < argc; ++i)
    {
        if (i == 0)
        {
            // Don't print the first argument as its value will change depending on the platform
            std::cout << "argv[" << i << "]: " << "*** skipped ***" << std::endl;
        }
        else
        {
            std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
        }
    }

#if defined(__linux__)
    extern char** environ;
    for (char** p = environ; *p != nullptr; ++p)
    {
        std::cout << *p << std::endl;
    }
#elif defined(_WIN32)
    char* environment = GetEnvironmentStrings();
    for (char* p = environment; *p != '\0'; ++p)
    {
        std::cout << p << std::endl;
        do
        {
            ++p;
        } while (*p != '\0');
    }
    FreeEnvironmentStrings(environment);
#endif
    
    return 0;
}
