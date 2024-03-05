#ifndef __TSCP_EXTENSIONS_FUNCTIONS_HPP
#	define __TSCP_EXTENSIONS_FUNCTIONS_HPP

#	include <string.h>
#	include <ctype.h>
#	include <vector>

namespace Functions {
	void clearString(char* buffer, size_t bufferSize);
	void toLowerString(char* buffer, size_t bufferSize, const char* src);
	void toUpperString(char* buffer, size_t bufferSize, const char* src);
	void swapCaseString(char* buffer, size_t bufferSize, const char* src);
	void subString(char* buffer, size_t bufferSize, const char* src, size_t start, size_t count);
	bool parseBool(const char* src);
	void eraseString(char* src, size_t bufferSize, char del);
	size_t countChar(const char* src, char c);
	void splitString(char* buffer, size_t bufferSize, const char* src, char c, size_t item);

}// namespace Functions


#endif