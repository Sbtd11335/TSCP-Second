#include "Config.hpp"

// Constructor
Config::Config(const char* fileName)
{
	strcpy_s(this->fileName, sizeof(this->fileName), fileName);
}
// Methods
bool Config::load()
{
	char line[__CONFIG_BUFFERSIZE]{}, ss[__CONFIG_BUFFERSIZE]{};
	FILE* file{};
	fopen_s(&file, fileName, "r");
	if (file == nullptr)
	{
		Error::error("Configファイルが見つかりませんでした。");
		return false;
	}
	while ((fgets(line, sizeof(line), file)) != NULL)
	{
		// Screen
		Functions::subString(ss, sizeof(ss), line, 0, 11);
		if (_stricmp(ss, "FullScreen:") == 0)
		{
			Functions::subString(ss, sizeof(ss), line, 11, strlen(line) - 11);
			Functions::eraseString(ss, sizeof(ss), '\n');
			fullScreen = Functions::parseBool(ss);
		}
		Functions::subString(ss, sizeof(ss), line, 0, 6);
		if (_stricmp(ss, "VSync:") == 0)
		{
			Functions::subString(ss, sizeof(ss), line, 6, strlen(line) - 6);
			Functions::eraseString(ss, sizeof(ss), '\n');
			vSync = Functions::parseBool(ss);
		}
		// Texture
		Functions::subString(ss, sizeof(ss), line, 0, 14);
		if (_stricmp(ss, "TextureFolder:") == 0)
		{
			Functions::subString(ss, sizeof(ss), line, 14, strlen(line) - 14);
			Functions::eraseString(ss, sizeof(ss), '\n');
			if (ss[strlen(ss) - 1] == '/')
				strcpy_s(textureFolder, sizeof(textureFolder), ss);
			else
				sprintf_s(textureFolder, sizeof(textureFolder), "%s/", ss);
		}
		// Sound
		Functions::subString(ss, sizeof(ss), line, 0, 12);
		if (_stricmp(ss, "SoundFolder:") == 0)
		{
			Functions::subString(ss, sizeof(ss), line, 12, strlen(line) - 12);
			Functions::eraseString(ss, sizeof(ss), '\n');
			if (ss[strlen(ss) - 1] == '/')
				strcpy_s(soundFolder, sizeof(soundFolder), ss);
			else
				sprintf_s(soundFolder, sizeof(soundFolder), "%s/", ss);
		}
		// Fumen
		Functions::subString(ss, sizeof(ss), line, 0, 12);
		if (_stricmp(ss, "FumenFolder:") == 0)
		{
			Functions::subString(ss, sizeof(ss), line, 12, strlen(line) - 12);
			Functions::eraseString(ss, sizeof(ss), '\n');
			if (ss[strlen(ss) - 1] == '/')
				strcpy_s(fumenFolder, sizeof(fumenFolder), ss);
			else
				sprintf_s(fumenFolder, sizeof(fumenFolder), "%s/", ss);
		}
		// Mods
		Functions::subString(ss, sizeof(ss), line, 0, 11);
		if (_stricmp(ss, "ModsFolder:") == 0)
		{
			Functions::subString(ss, sizeof(ss), line, 11, strlen(line) - 11);
			Functions::eraseString(ss, sizeof(ss), '\n');
			if (ss[strlen(ss) - 1] == '/')
				strcpy_s(modsFolder, sizeof(modsFolder), ss);
			else
				sprintf_s(modsFolder, sizeof(modsFolder), "%s/", ss);
		}
	}


	fclose(file);
	return true;
}
// Getter
const char* Config::getTextureFolder() const { return const_cast<const char*>(textureFolder); }
const char* Config::getSoundFolder() const { return const_cast<const char*>(soundFolder); }
const char* Config::getFumenFolder() const { return const_cast<const char*>(fumenFolder); }
const char* Config::getModsFolder() const { return const_cast<const char*>(modsFolder); }