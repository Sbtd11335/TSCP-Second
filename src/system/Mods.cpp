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
		{
			modFinal();
			FreeLibrary(mods[mCount]);
		}			
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
				if (modsFolder[strlen(modsFolder) - 1] == '/')
					sprintf_s(modFile, sizeof(modFile), "%s%s", modsFolder, modsDirent->d_name);
				else
					sprintf_s(modFile, sizeof(modFile), "%s/%s", modsFolder, modsDirent->d_name);
				HMODULE mod = LoadLibraryA(modFile);
				if (mod != NULL)
				{
					mods.push_back(mod);
					//initialize
					__Function* modFunc = (__Function*)GetProcAddress(mod, "__INITIALIZE");
					if (modFunc != nullptr)
						(*modFunc)();
					modFunc = nullptr;
					//functionSize
					functionSize = 64;
					__Constant* modConst = (__Constant*)GetProcAddress(mod, "__FUNCTIONSIZE");
					if (modConst != nullptr)
						functionSize = *(size_t*)(modConst);
					printf("%zd\n", functionSize);
					modConst = nullptr;
					//function
					char* function = new char[functionSize] {};
					char* funcName = new char[functionSize] {};
					char* funcSub = new char[functionSize] {};
					modConst = (__Constant*)GetProcAddress(mod, "__FUNCTION");
					if (modConst != nullptr)
					{
						strcpy_s(function, functionSize, *(const char**)modConst);
						for (size_t fCount{}; fCount < Functions::countChar(function, ',') + 1; fCount++)
						{
							Functions::splitString(funcName, functionSize, function, ',', fCount);
							__Function* modFunction = (__Function*)GetProcAddress(mod, funcName);
							if (modFunction != nullptr)
							{
								// __SCENE
								Functions::subString(funcSub, functionSize, funcName, 0, 7);
								if (strcmp(funcSub, "__SCENE") == 0)
								{
									window.appendScene((Scene*)(*modFunction)());
									continue;
								}
								(*modFunction)();
							}
						}
					}
					delete[]function;
					delete[]funcName;
					delete[]funcSub;
				}
			}
		}
	}

	closedir(modsDIR);
	return;
}
