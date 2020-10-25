/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include <cstdlib>

int main(int argc, char* argv[])
{
    int exitCode = 0;

    if (argc > 1)
    {
        exitCode = atoi(argv[1]);
    }

    return exitCode;
}
