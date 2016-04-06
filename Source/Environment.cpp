/*
	Copyright (c) 2005-2015 Xavier Leclercq

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OROTHER DEALINGS
	IN THE SOFTWARE.
*/

#include "Environment.h"
#include <stdlib.h>

namespace Ishiko
{
namespace EnvironmentVariables
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
	_putenv_s(name.c_str(), value.c_str());
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
