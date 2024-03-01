#ifndef __SYSTEM_MODS_HPP
#	define __SYSTEM_MODS_HPP

#	include "../Macro.hpp"
#	include "Window.hpp"
#	include "../extensions/dirent.h"
#	include "../extensions/Functions.hpp"
#	include <Windows.h>
#	include <string.h>
#	include <vector>

typedef void* __Function();

class Mods {
private:
	char modsFolder[__FILE_BUFFERSIZE]{};
	std::vector<HMODULE>mods;

public:
	// Constructor
	Mods(const char* modsFolder);
	// Destructor
	~Mods();
	// Methods
	void load();
};

#endif