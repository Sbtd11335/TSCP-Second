#include "Main.hpp"

int main(int argc, char* argv[])
{
	// Config
	Config config("Config.ini");
	config.load();
	// Mods
	Mods mods(config.getModsFolder());
	mods.load();

	std::thread windowThread([]() { mainWindow.create(); });
	windowThread.join();
	return 0;
}
