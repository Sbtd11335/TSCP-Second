#ifndef __TSCP_SYSTEM_FILEREADER_HPP
#	define __TSCP_SYSTEM_FILEREADER_HPP

#	include "../Macro.hpp"
#	include "../extensions/Functions.hpp"
#	include <stdio.h>
#	include <string.h>
#	include <wchar.h>

enum Encode {
	__ANSI,
	__SHIFT_JIS = __ANSI,
	__UTF_8,
};

class FileReader {
protected:
	char fileName[__FILE_BUFFERSIZE]{};
	Encode encode{ Encode::__ANSI };
	bool isExists{};

public:
	FileReader(const char* fileName);
	// Method
	virtual void load();
	template<typename Type>void allocation(Type* buffer, const char* variableName, const char* line, size_t lineSize);
	template<typename Type>void allocation(bool* buffer, const char* variableName, const char* line, size_t lineSize);
	template<typename Type>void allocation(char* buffer, size_t buffetSize, const char* variableName, const char* line, size_t lineSize);
	// Getter
	bool exists() const;
	Encode getEncode() const;
	const char* getFileName() const;
};

template<typename Type>void FileReader::allocation(Type* buffer, const char* variableName, const char* line, size_t lineSize)
{
	char* str = new char[lineSize] {}, * param = new char[lineSize] {}, * sub = new char[lineSize] {};
	sprintf_s(str, lineSize, "%s:", variableName);
	Functions::subString(param, lineSize, line, strlen(variableName) + 1, strlen(line) - (strlen(variableName) + 1));
	Functions::subString(sub, lineSize, line, 0, strlen(str));
	if (_strcmpi(sub, str) == 0)
		*buffer = atof(param);
	delete[] str;
	delete[] param;
	delete[] sub;
}
template<typename Type>void FileReader::allocation(bool* buffer, const char* variableName, const char* line, size_t lineSize)
{
	char* str = new char[lineSize] {}, * param = new char[lineSize] {}, * sub = new char[lineSize] {};
	sprintf_s(str, lineSize, "%s:", variableName);
	Functions::subString(param, lineSize, line, strlen(variableName) + 1, strlen(line) - (strlen(variableName) + 1));
	Functions::subString(sub, lineSize, line, 0, strlen(str));
	if (_strcmpi(sub, str) == 0)
		*buffer = Functions::parseBool(param);
	delete[] str;
	delete[] param;
	delete[] sub;
}
template<typename Type>void FileReader::allocation(char* buffer, size_t buffetSize, const char* variableName, const char* line, size_t lineSize)
{
	char* str = new char[lineSize] {}, * param = new char[lineSize] {}, * sub = new char[lineSize] {};
	sprintf_s(str, lineSize, "%s:", variableName);
	Functions::subString(param, lineSize, line, strlen(variableName) + 1, strlen(line) - (strlen(variableName) + 1));
	Functions::subString(sub, lineSize, line, 0, strlen(str));
	if (_strcmpi(sub, str) == 0)
		strcpy_s(buffer, sizeof(buffer), param);
	delete[] str;
	delete[] param;
	delete[] sub;
}

#endif