#ifndef __TSCP_SYSTEM_MODS_HPP
#	define __TSCP_SYSTEM_MODS_HPP

#	include "../Macro.hpp"
#	include "Window.hpp"
#	include "../extensions/dirent.h"
#	include "../extensions/Functions.hpp"
#	include <Windows.h>
#	include <string.h>
#	include <vector>

typedef void* __Function();
typedef void* __Constant;
extern Window window;
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