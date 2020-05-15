/*
    Copyright (c) 2005-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#include "Environment.h"
#include <stdlib.h>

namespace Ishiko
{
namespace Process
{

bool Environment::find(const std::string& name, std::string& value)
{
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
}

void Environment::set(const std::string& name, 
                      const std::string& value)
{
#ifdef _WIN32
    _putenv_s(name.c_str(), value.c_str());
#elif __linux__
    setenv(name.c_str(), value.c_str(), 1);
#else
    #error Unsupported platform
#endif
}

std::string Environment::expandVariablesInString(const std::string& str,
                                                 int format)
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
				bool found = find(name, value);
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
