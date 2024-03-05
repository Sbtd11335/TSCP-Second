#include "Config.hpp"


// Methods
void Config::load()
{
	if (exists() == false)
		Error::error("Configファイルが見つかりませんでした。");

	char line[__CONFIG_BUFFERSIZE]{}, ss[__CONFIG_BUFFERSIZE]{};
	FILE* file{};
	fopen_s(&file, fileName, "r");
	if (file == nullptr)
	{
		Error::error("Configファイルの読み込みに失敗しました。");
		return;
	}
	while ((fgets(line, sizeof(line), file)) != NULL)
	{
		Functions::eraseString(line, sizeof(line), '\n');
		/* Screen */
		allocation<bool>(&fullScreen, "FullScreen", line, __CONFIG_BUFFERSIZE);
		allocation<bool>(&vSync, "VSync", line, __CONFIG_BUFFERSIZE);
		/* Texture */
		allocation<char*>(textureFolder, sizeof(textureFolder), "TextureFolder", line, __CONFIG_BUFFERSIZE);
		/* Sound */
		allocation<char*>(soundFolder, sizeof(soundFolder), "SoundFolder", line, __CONFIG_BUFFERSIZE);
		/* Fumen */
		allocation<char*>(fumenFolder, sizeof(fumenFolder), "FumenFolder", line, __CONFIG_BUFFERSIZE);
		/* Mods */
		allocation<char*>(modsFolder, sizeof(modsFolder), "ModsFolder", line, __CONFIG_BUFFERSIZE);
	}

	fclose(file);
}
// Getter
bool Config::getFullScreen() const { return fullScreen; }
bool Config::getVSync() const { return vSync; }
const char* Config::getTextureFolder() const { return const_cast<const char*>(textureFolder); }
const char* Config::getSoundFolder() const { return const_cast<const char*>(soundFolder); }
const char* Config::getFumenFolder() const { return const_cast<const char*>(fumenFolder); }
const char* Config::getModsFolder() const { return const_cast<const char*>(modsFolder); }