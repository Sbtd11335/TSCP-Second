#include "functions.hpp"
#include <stdio.h>

void Functions::clearString(char* buffer, size_t bufferSize)
{
	for (size_t count{}; count < bufferSize; count++)
	{
		buffer[count] = '\0';
	}
}
void Functions::toLowerString(char* buffer, size_t bufferSize, const char* src)
{
	Functions::clearString(buffer, bufferSize);
	for (size_t count{}; count < strlen(src) && count < bufferSize; count++)
	{
		if (src[count] >= 'A' && src[count] <= 'Z')
			buffer[count] = tolower(src[count]);
		else
			buffer[count] = src[count];
	}
}
void Functions::toUpperString(char* buffer, size_t bufferSize, const char* src)
{
	Functions::clearString(buffer, bufferSize);
	for (size_t count{}; count < strlen(src) && count < bufferSize; count++)
	{
		if (src[count] >= 'a' && src[count] <= 'z')
			buffer[count] = toupper(src[count]);
		else
			buffer[count] = src[count];
	}
}
void Functions::swapCaseString(char* buffer, size_t bufferSize, const char* src)
{
	Functions::clearString(buffer, bufferSize);
	for (size_t count{}; count < strlen(src) && count < bufferSize; count++)
	{
		if (src[count] >= 'a' && src[count] <= 'z')
			buffer[count] = toupper(src[count]);
		else if (src[count] >= 'A' && src[count] <= 'Z')
			buffer[count] = tolower(src[count]);
		else
			buffer[count] = src[count];
	}
}
void Functions::subString(char* buffer, size_t bufferSize, const char* src, size_t start, size_t count)
{
	Functions::clearString(buffer, bufferSize);
	for (size_t ccount{ start }; ccount < start + count; ccount++)
	{
		if (ccount >= strlen(src) || ccount - start >= bufferSize)
			break;
		buffer[ccount - start] = src[ccount];
	}
}
bool Functions::parseBool(const char* src)
{
	if (_strcmpi(src, "True") == 0 || _strcmpi(src, "1") == 0)
		return true;
	return false;
}
void Functions::eraseString(char* src, size_t bufferSize, char del)
{
	char* get = new char[bufferSize * 2] {};
	for (size_t count{}, count2{}; count < strlen(src); count++)
	{
		if (src[count] != del)
		{
			get[count2++] = src[count];
		}
	}
	strcpy_s(src, bufferSize, get);
	delete[]get;
}
size_t Functions::countChar(const char* src, char c)
{
	size_t ccount{};
	for (size_t count{}; count < strlen(src); count++)
	{
		if (src[count] == c)
			ccount++;
	}
	return ccount;
}
void Functions::splitString(char* buffer, size_t bufferSize, const char* src, char c, size_t item)
{
	size_t ccount{};
	Functions::clearString(buffer, bufferSize);
	for (size_t count{}, count2{}; count < strlen(src); count++)
	{
		if (src[count] == c)
		{
			if (ccount == item)
				return;
			count2 = 0;
			ccount++;
			Functions::clearString(buffer, bufferSize);
		}
		else {
			buffer[count2++] = src[count];
		}
	}
	if (item > ccount)
		Functions::clearString(buffer, bufferSize);
}
