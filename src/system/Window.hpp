#ifndef __SYSTEM_WINDOW_HPP
#	define __SYSTEM_WINDOW_HPP

#	pragma comment(lib, "glfw3.lib")
#	pragma comment(lib, "opengl32.lib")

#	include "../Macro.hpp"
#	include "Error.hpp"
#	include <GLFW/glfw3.h>
#	include <Windows.h>
#	include <stdio.h>
#	include <string.h>

class Window {
private:
	static int __GLFWINIT;

	int width{}, height{}, nWidth{}, nHeight{};
	char  status{ -1 }, title[__TITLE]{};
	bool fullScreen{}, vSync{}, getInformation{};
	GLFWwindow* window{ nullptr };

public:
	// Constructor
	Window();
	Window(const char* title);
	Window(int width, int height);
	Window(int width, int height, const char* title);
	// Methods
	void create(bool fullScreen = false, bool vSync = false);
	// Getter
	GLFWwindow* getWindow() const;
	bool isKeyDown(int key);
	bool isMouseButtonDown(int Button);
	char getStatus() const;
};

#endif