/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ChildProcessBuilder.h"
#include "ErrorCategory.h"
#ifdef __linux__
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace Ishiko
{
namespace Process
{

ChildProcess ChildProcessBuilder::StartProcess(const std::string& commandLine, Error& error)
{
    ChildProcessBuilder builder(commandLine);
    return builder.start(error);
}

ChildProcessBuilder::ChildProcessBuilder(const CommandLine& commandLine)
    : m_commandLine(commandLine)
{
}

ChildProcess ChildProcessBuilder::start(Error& error)
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

    HANDLE handle = INVALID_HANDLE_VALUE;
    if (!CreateProcessA(NULL, const_cast<char*>(m_commandLine.toString().c_str()),
        NULL, NULL, inheritHandles, 0, NULL, NULL, &startupInfo, &processInfo))
    {
        ErrorCategory::Fail(error, ErrorCategory::eGeneric);
    }
    else
    {
        handle = processInfo.hProcess;
        CloseHandle(processInfo.hThread);
    }

    if (!m_standardOutputFilePath.empty())
    {
        CloseHandle(outputFile);
    }

    return ChildProcess(handle);
#else
    error.fail(-1);
    return ChildProcess();
#endif
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
