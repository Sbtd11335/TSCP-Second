#include "Mods.hpp"

// Contructor
Mods::Mods(const char* modsFolder)
{
	strcpy_s(this->modsFolder, sizeof(this->modsFolder), modsFolder);
}
// Destructor
Mods::~Mods()
{
	for (size_t mCount{}; mCount < mods.size(); mCount++)
	{
		__Function* modFinal = (__Function*)GetProcAddress(mods[mCount], "__FINALIZE");
		if (modFinal != nullptr)
			modFinal();
	}
}
// Methods
void Mods::load()
{
	dirent* modsDirent{ nullptr };
	DIR* modsDIR{ nullptr };
	char modFile[__FILE_BUFFERSIZE * 2]{};
	char dll[5]{};
	size_t functionSize{};
	modsDIR = opendir(modsFolder);
	if (modsDIR == nullptr)
		return;
	modsDirent = readdir(modsDIR);
	modsDirent = readdir(modsDIR);
	while ((modsDirent = readdir(modsDIR)) != nullptr)
	{
		if (modsDirent->d_type != DT_DIR && strlen(modsDirent->d_name) >= 4)
		{
			sprintf_s(dll, sizeof(dll), "%4s", &modsDirent->d_name[strlen(modsDirent->d_name) - 4]);
			if (_stricmp(dll, ".dll") == 0)
			{
				sprintf_s(modFile, sizeof(modFile), "%s%s", modsFolder, modsDirent->d_name);
				HMODULE mod = LoadLibraryA(modFile);
				if (mod != NULL)
				{
					mods.push_back(mod);
					//initialize
					__Function* modFunc = (__Function*)GetProcAddress(mod, "__INITIALIZE");
					if (modFunc != nullptr)
						(*modFunc)();
					modFunc = nullptr;
					//targetSize
					functionSize = 64;
					modFunc = (__Function*)GetProcAddress(mod, "__FUNCTIONSIZE");
					if (modFunc != nullptr)
						functionSize = (size_t)(*modFunc)();
					modFunc = nullptr;
					//Function
					char* function = new char[functionSize] {};
					char* funcName = new char[functionSize] {};
					modFunc = (__Function*)GetProcAddress(mod, "__FUNCTION");
					if (modFunc != nullptr)
					{
						strcpy_s(function, functionSize, (const char*)modFunc());
						for (size_t fCount{}; fCount < Functions::countChar(function, ',') + 1; fCount++)
						{
							Functions::splitString(funcName, functionSize, function, ',', fCount);
							__Function* modFunction = (__Function*)GetProcAddress(mod, funcName);
							if (modFunction != nullptr)
								(*modFunction)();
						}
					}
					delete[]function;
					delete[]funcName;
				}
			}
		}
	}

	closedir(modsDIR);
	return;
}
