#include "Error.hpp"

void Error::error(const char* msg, int errorCode)
{
	MessageBoxA(NULL, msg, __PROJECT, MB_ICONERROR);
	exit(errorCode);
}