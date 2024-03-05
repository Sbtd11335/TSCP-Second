#include "Main.hpp"

class GetWC : public FileReader {
private:
	wchar_t get[256]{};

public:
	using FileReader::FileReader;
	void load() override
	{
		FILE* file{};
		fopen_s(&file, fileName, "r,ccs=UTF-8");
		if (file == nullptr)
			return;
		fgetws(get, sizeof(get), file);
		fclose(file);
	}
	const wchar_t* getText() { return const_cast<const wchar_t*>(get); }
};

int main(int argc, char* argv[])
{
	//Sound
	Sound::setUp(&argc, argv);
	// Config
	Config config("Config.ini");
	config.load();
	// Mods
	Mods mods(config.getModsFolder());
	mods.load();


	std::thread windowThread([&config]() { window.create(config.getFullScreen(), config.getVSync()); });
	windowThread.join();
	Sound::End();
	return 0;
}

