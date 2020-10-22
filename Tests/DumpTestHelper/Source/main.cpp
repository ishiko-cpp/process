/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#undef UNICODE
#include <Windows.h>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "argc: " << argc << std::endl;
    for (int i = 0; i < argc; ++i)
    {
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }

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
    
    return 0;
}
