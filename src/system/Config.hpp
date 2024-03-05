#ifndef __TSCP_SYSTEM_CONFIG_HPP
#	define __TSCP_SYSTEM_CONFIG_HPP

#	include "FileReader.hpp"
#	include "../Macro.hpp"
#	include "../extensions/Functions.hpp"
#	include "Error.hpp"
#	include <stdio.h>
#	include <string.h>

class Config : public FileReader{
private:
	bool fullScreen{}, vSync{};
	char textureFolder[__FILE_BUFFERSIZE]{};
	char soundFolder[__FILE_BUFFERSIZE]{};
	char fumenFolder[__FILE_BUFFERSIZE]{};
	char modsFolder[__FILE_BUFFERSIZE]{};

public:
	using FileReader::FileReader;
	// Methods
	void load() override;
	//Getter
	bool getFullScreen() const;
	bool getVSync() const;
	const char* getTextureFolder() const;
	const char* getSoundFolder() const;
	const char* getFumenFolder() const;
	const char* getModsFolder() const;
};

#endif