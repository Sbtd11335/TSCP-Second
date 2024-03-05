#ifndef __TSCP_SYSTEM_WINDOW_HPP
#	define __TSCP_SYSTEM_WINDOW_HPP

#	pragma comment(lib, "glfw3.lib")
#	pragma comment(lib, "opengl32.lib")

#	include "../Macro.hpp"
#	include "Error.hpp"
#	include "Scene.hpp"
#	include <GLFW/glfw3.h>
#	include <Windows.h>
#	include <stdio.h>
#	include <string.h>
#	include <vector>

class Window {
private:
	static int __GLFWINIT;
	int width{}, height{}, nWidth{}, nHeight{}, fps{};
	char  status{ -1 }, title[__TITLE]{};
	bool fullScreen{}, vSync{}, getInformation{};
	SceneID nowScene = { SceneID::boot };
	std::vector<std::vector<Scene*>>scenes;
	std::vector<std::vector<bool>>isSceneInitialized;
	GLFWwindow* window{ nullptr };
public:
	// Constructor
	Window();
	Window(const char* title);
	Window(int width, int height);
	Window(int width, int height, const char* title);
	// Methods
	void create(bool fullScreen = false, bool vSync = false);
	void appendScene(Scene* scene);
	void changeScene(SceneID sceneID);
	void initScenes();
	// Getter
	GLFWwindow* getWindow() const;
	bool isKeyDown(int key);
	bool isMouseButtonDown(int Button);
	char getStatus() const;
	SceneID getNowScene() const;
	size_t getSceneCount(SceneID sceneID) const;

};

#endif