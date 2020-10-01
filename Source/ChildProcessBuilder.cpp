/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "ChildProcessBuilder.h"
#include "ErrorCategory.h"
#ifdef __linux__
#include <boost/filesystem/operations.hpp>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace Ishiko
{
namespace Process
{

ChildProcess ChildProcessBuilder::StartProcess(const std::string& commandLine, Error& error)
{
    ChildProcessBuilder builder{CommandLine(commandLine)};
    return builder.start(error);
}

ChildProcessBuilder::ChildProcessBuilder(const std::string& commandLine)
    : ChildProcessBuilder(CommandLine(commandLine))
{
}

ChildProcessBuilder::ChildProcessBuilder(const CommandLine& commandLine)
    : m_commandLine(commandLine)
{
}

ChildProcess ChildProcessBuilder::start(Error& error)
{
#if defined(__linux__)
    if (!boost::filesystem::exists(m_commandLine.getExecutable(CommandLine::eRaw)))
    {
        Fail(error, ErrorCategory::eGeneric);
        return ChildProcess(-1);
    }
    pid_t child = fork();
    if (child == -1)
    {
        // TODO
        Fail(error, ErrorCategory::eGeneric);
        return ChildProcess(child);
    } 
    else if (child > 0)
    {
        return ChildProcess(child);
    }
    else
    {
        std::vector<std::string> arguments = m_commandLine.getArguments(CommandLine::eRaw);
        char** argv = new char*[arguments.size() + 2];
        size_t i = 0;
        argv[i] = strdup(m_commandLine.getExecutable(CommandLine::eRaw).c_str());
        ++i;
        for (const std::string& argument : arguments)
        {
            argv[i] = strdup(argument.c_str());
            ++i;
        }
        argv[i] = nullptr;

        if (!m_standardOutputFilePath.empty())
        {
            // TODO: what permissions?
            int fd = open(m_standardOutputFilePath.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0400);
            dup2(fd, STDOUT_FILENO);
        }

        int err = execv(m_commandLine.getExecutable(CommandLine::eRaw).c_str(), argv);
        // TODO: how to feed back a better error to the parent process?
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
    if (!CreateProcessA(NULL, const_cast<char*>(m_commandLine.toString(CommandLine::eQuoteIfNeeded).c_str()),
        NULL, NULL, inheritHandles, 0, NULL, NULL, &startupInfo, &processInfo))
    {
        Fail(error, ErrorCategory::eGeneric);
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
    Fail(error, ErrorCategory::eGeneric);
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
