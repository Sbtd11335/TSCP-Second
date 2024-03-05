#ifndef __TSCP_MOD
#	define __TSCP_MOD

#	include "system/Scene.hpp"
#	include "system/Window.hpp"
#	include <Windows.h>
#	include <TlHelp32.h>

#	ifdef DLLEXPORT
#		define DLLEXPORT __declspec(dllexport)
#	else
#		define DLLEXPORT __declspec(dllexport)
#	endif

HFONT font = CreateFontW(32, 0, 0, 0, 0, false, false, false, SHIFTJIS_CHARSET, OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 0, L"FOT-ëÂç]åÀä®í‡ó¨ Std E");

extern "C" {
	DLLEXPORT void __INITIALIZE();
	DLLEXPORT size_t __FUNCTIONSIZE = 256;
	DLLEXPORT const char* __FUNCTION = "__SCENE_BOOT";

	DLLEXPORT class Boot : public Scene {
	private:
		bool overLay{};
		uint32_t f9Count{};
		Texture tex{ Texture("Texture/Back.png") };
		Sound main{ Sound("Sound/Main.wav") };
		Text text{ Text("23éû54ï™ÅAózÇÃó∑òHÇ÷ÇÃÉvÉåÉäÉÖÅ[Éh", &font) };

	public:
		Boot();
		void init() override;
		void final() override;
		void draw() override;
		void over() override;
		void end() override;
	};

	DLLEXPORT Boot* scene{ nullptr };
	DLLEXPORT Boot* __SCENE_BOOT();
}


#endif