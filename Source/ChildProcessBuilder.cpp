/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ChildProcessBuilder.h"
#ifdef __linux__
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace Ishiko
{
namespace Process
{

int ChildProcessBuilder::StartProcess(const std::string& commandLine, ProcessHandle& handle)
{
    ChildProcessBuilder builder(commandLine);
    return builder.start(handle);
}

ChildProcessBuilder::ChildProcessBuilder(const std::string& commandLine)
    : m_commandLine(commandLine)
{
}

int ChildProcessBuilder::start(ProcessHandle& handle)
{
#if defined(__linux__)
    pid_t child = fork();
    if (child == -1)
    {
        // TODO
    } 
    else if (child > 0)
    {
    }
    else
    {
        char* argv[1];
        int err = execv(m_commandLine.c_str(), argv);
        exit(-1);
    }
#elif defined(_WIN32)
    STARTUPINFOA startupInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

    HANDLE outputFile;
    BOOL inheritHandles = FALSE;
    if (!m_standardOutputFilePath.empty())
    {
        inheritHandles = TRUE;
        outputFile = createInheritableFile(m_standardOutputFilePath);
        startupInfo.dwFlags |= STARTF_USESTDHANDLES;
        startupInfo.hStdOutput = outputFile;
    }

    PROCESS_INFORMATION processInfo;
    ZeroMemory(&processInfo, sizeof(processInfo));

    if (!CreateProcessA(NULL, const_cast<char*>(m_commandLine.c_str()),
        NULL, NULL, inheritHandles, 0, NULL, NULL, &startupInfo, &processInfo))
    {
        return -1;
    }
    else
    {
        handle.assign(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        return 0;
    }

    if (!m_standardOutputFilePath.empty())
    {
        CloseHandle(outputFile);
    }
#endif

    return -1;
}

void ChildProcessBuilder::redirectStandardOutputToFile(const std::string& path)
{
    m_standardOutputFilePath = path;
}

#ifdef _WIN32
HANDLE ChildProcessBuilder::createInheritableFile(const std::string& path)
{
    SECURITY_ATTRIBUTES securityAttributes;
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = TRUE;
    securityAttributes.lpSecurityDescriptor = NULL;
    return CreateFileA(path.c_str(), FILE_APPEND_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ,
        &securityAttributes, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}
#endif


}
}
