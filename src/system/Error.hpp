#ifndef __TSCP_SYSTEM_ERROR_HPP
#	define __TSCP_SYSTEM_ERROR_HPP

#	include "../Macro.hpp"
#	include <Windows.h>

namespace Error {
	void error(const char* msg, int errorCode = 1);
}

#endif