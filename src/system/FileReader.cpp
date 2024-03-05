#include "FileReader.hpp"

/* class FileReader */
// Constructor
FileReader::FileReader(const char* fileName)
{
	strcpy_s(this->fileName, sizeof(this->fileName), fileName);
	//Encode
	FILE* file{};
	char encode[32]{};
	fopen_s(&file, fileName, "r");
	if (file == nullptr)
		return;
	fgets(encode, sizeof(encode), file);
	if (_stricmp(encode, "*ANSI") == 0 || _stricmp(encode, "*SHIFT-JIS") == 0 || _stricmp(encode, "*SJIS") == 0 || _stricmp(encode, "*SHIFTJIS") == 0)
		this->encode = Encode::__ANSI;
	else if (_stricmp(encode, "*UTF-8") == 0 || _stricmp(encode, "*UTF8") == 0)
		this->encode = Encode::__UTF_8;
	fclose(file);
	isExists = true;
}
void FileReader::load()
{

}
bool FileReader::exists() const { return isExists; }
Encode FileReader::getEncode() const { return encode; }
const char* FileReader::getFileName() const { return const_cast<const char*>(fileName); }
