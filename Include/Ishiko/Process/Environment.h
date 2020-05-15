/*
    Copyright (c) 2005-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Process/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_PROCESS_ENVIRONMENT_H_
#define _ISHIKO_PROCESS_ENVIRONMENT_H_

#include <string>

namespace Ishiko
{
namespace Process
{

class Environment
{
public:
	enum EReferenceFormat
	{
		eDollarAndParentheses = 0x01
	};

public:
	static bool find(const std::string& name, std::string& value);
	static void set(const std::string& name, const std::string& value);

	static std::string expandVariablesInString(const std::string& str, 
		int format);
};

}
}

#include "linkoptions.h"

#endif
