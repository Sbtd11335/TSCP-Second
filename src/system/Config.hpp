#ifndef __SYSTEM_CONFIG_HPP
#	define __SYSTEM_CONFIG_HPP

#	include "../Macro.hpp"
#	include "../extensions/Functions.hpp"
#	include "Error.hpp"
#	include <stdio.h>
#	include <string.h>

class Config {
private:
	char fileName[__FILE_BUFFERSIZE]{};
	// Config
	bool fullScreen{}, vSync{};
	char textureFolder[__FILE_BUFFERSIZE]{};
	char soundFolder[__FILE_BUFFERSIZE]{};
	char fumenFolder[__FILE_BUFFERSIZE]{};
	char modsFolder[__FILE_BUFFERSIZE]{};

public:
	// Constructor
	Config(const char* fileName);
	// Methods
	bool load();
	//Getter
	const char* getTextureFolder() const;
	const char* getSoundFolder() const;
	const char* getFumenFolder() const;
	const char* getModsFolder() const;
};

#endif