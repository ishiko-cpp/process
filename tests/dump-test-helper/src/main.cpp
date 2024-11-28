// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

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
    std::cout << "\nenv: " << std::endl;
    extern char** environ;
    for (char** p = environ; *p != nullptr; ++p)
    {
        std::cout << *p << std::endl;
    }

    std::cout << "\ncwd: " << getcwd(nullptr, 0) << std::endl;
#elif defined(_WIN32)
    std::cout << "\nenv: " << std::endl;
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

    char cwd[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, cwd);
    std::cout << "\ncwd: " << cwd << std::endl;
#endif
    
    return 0;
}
