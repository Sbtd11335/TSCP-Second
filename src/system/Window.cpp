#include "Window.hpp"

int Window::__GLFWINIT = glfwInit();

// Constructor
Window::Window()
{
	width = 640;
	height = 480;
	strcpy_s(title, sizeof(title), "");
	Window::initScenes();
}
Window::Window(const char* title)
{
	width = 640;
	height = 480;
	strcpy_s(this->title, sizeof(this->title), title);
	Window::initScenes();
}
Window::Window(int width, int height)
{
	this->width = width;
	this->height = height;
	strcpy_s(title, sizeof(title), "");
	Window::initScenes();
}
Window::Window(int width, int height, const char* title)
{
	this->width = width;
	this->height = height;
	strcpy_s(this->title, sizeof(this->title), title);
	Window::initScenes();
}
// Methods
void Window::create(bool fullScreen, bool vSync)
{
	int fpsCounter{}, C{};
	std::chrono::system_clock::time_point time{};
	status = -1;
	if (__GLFWINIT == GLFW_FALSE)
	{
		Error::error("GLFW‚Ì‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
		return;
	}
	this->fullScreen = fullScreen;
	this->vSync = vSync;
	if (fullScreen == false)
		window = glfwCreateWindow(width, height, title, NULL, NULL);
	else
	{
		ShowCursor(false);
		window = glfwCreateWindow(1920, 1080, title, glfwGetPrimaryMonitor(), NULL);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(static_cast<int>(vSync));
	glfwShowWindow(window);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	status = 0;
	//once
	for (size_t nc{}; nc < static_cast<size_t>(SceneID::result); nc++)
	{
		for (size_t sc{}; sc < Window::getSceneCount(static_cast<SceneID>(nc)); sc++)
		{
			scenes[nc][sc]->once();
		}
	}
	time = std::chrono::system_clock::now();
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		getInformation = false;
		glfwGetWindowSize(window, &nWidth, &nHeight);
		getInformation = true;
		glViewport(0, 0, nWidth, nHeight);
		fpsCounter++;
		if (std::chrono::nanoseconds(std::chrono::system_clock::now() - time).count() / pow(10, 9) >= 1.0)
		{
			time = std::chrono::system_clock::now();
			fps = fpsCounter;
			fpsCounter = 0;
			printf("%d\n", fps);
		}
		if (isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
		{
			if (C == 0)
			{
				if (nowScene == SceneID::boot)
					changeScene(SceneID::title);
				else if (nowScene == SceneID::title)
					changeScene(SceneID::boot);
			}
			C++;
		}
		else
			C = 0;
		//draw
		switch (nowScene)
		{
		case SceneID::boot:
			for (size_t nc{}; nc < static_cast<size_t>(SceneID::result); nc++)
			{
				for (size_t sc{}; sc < Window::getSceneCount(static_cast<SceneID>(nc)); sc++)
				{
					if (nc != nowScene && isSceneInitialized[nc][sc])
					{
						scenes[nc][sc]->final();
						isSceneInitialized[nc][sc] = false;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] == false)
					{
						scenes[nc][sc]->init();
						isSceneInitialized[nc][sc] = true;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] && sc == Window::getSceneCount(static_cast<SceneID>(nc)) - 1)
					{
						scenes[nc][sc]->draw();
						scenes[nc][sc]->over();
					}
						
				}
			}
			break;
		case SceneID::title:
			for (size_t nc{}; nc < static_cast<size_t>(SceneID::result); nc++)
			{
				for (size_t sc{}; sc < Window::getSceneCount(static_cast<SceneID>(nc)); sc++)
				{
					if (nc != nowScene && isSceneInitialized[nc][sc])
					{
						scenes[nc][sc]->final();
						isSceneInitialized[nc][sc] = false;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] == false)
					{
						scenes[nc][sc]->init();
						isSceneInitialized[nc][sc] = true;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] && sc == Window::getSceneCount(static_cast<SceneID>(nc)) - 1)
					{
						scenes[nc][sc]->draw();
						scenes[nc][sc]->over();
					}
				}
			}
			break;
		case SceneID::entry:
			for (size_t nc{}; nc < static_cast<size_t>(SceneID::result); nc++)
			{
				for (size_t sc{}; sc < Window::getSceneCount(static_cast<SceneID>(nc)); sc++)
				{
					if (nc != nowScene && isSceneInitialized[nc][sc])
					{
						scenes[nc][sc]->final();
						isSceneInitialized[nc][sc] = false;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] == false)
					{
						scenes[nc][sc]->init();
						isSceneInitialized[nc][sc] = true;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] && sc == Window::getSceneCount(static_cast<SceneID>(nc)) - 1)
					{
						scenes[nc][sc]->draw();
						scenes[nc][sc]->over();
					}
				}
			}
			break;
		case SceneID::selectSong:
			for (size_t nc{}; nc < static_cast<size_t>(SceneID::result); nc++)
			{
				for (size_t sc{}; sc < Window::getSceneCount(static_cast<SceneID>(nc)); sc++)
				{
					if (nc != nowScene && isSceneInitialized[nc][sc])
					{
						scenes[nc][sc]->final();
						isSceneInitialized[nc][sc] = false;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] == false)
					{
						scenes[nc][sc]->init();
						isSceneInitialized[nc][sc] = true;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] && sc == Window::getSceneCount(static_cast<SceneID>(nc)) - 1)
					{
						scenes[nc][sc]->draw();
						scenes[nc][sc]->over();
					}
				}
			}
			break;
		case SceneID::playSong:
			for (size_t nc{}; nc < static_cast<size_t>(SceneID::result); nc++)
			{
				for (size_t sc{}; sc < Window::getSceneCount(static_cast<SceneID>(nc)); sc++)
				{
					if (nc != nowScene && isSceneInitialized[nc][sc])
					{
						scenes[nc][sc]->final();
						isSceneInitialized[nc][sc] = false;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] == false)
					{
						scenes[nc][sc]->init();
						isSceneInitialized[nc][sc] = true;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] && sc == Window::getSceneCount(static_cast<SceneID>(nc)) - 1)
					{
						scenes[nc][sc]->draw();
						scenes[nc][sc]->over();
					}
				}
			}
			break;
		case SceneID::result:
			for (size_t nc{}; nc < static_cast<size_t>(SceneID::result); nc++)
			{
				for (size_t sc{}; sc < Window::getSceneCount(static_cast<SceneID>(nc)); sc++)
				{
					if (nc != nowScene && isSceneInitialized[nc][sc])
					{
						scenes[nc][sc]->final();
						isSceneInitialized[nc][sc] = false;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] == false)
					{
						scenes[nc][sc]->init();
						isSceneInitialized[nc][sc] = true;
					}
					else if (nc == nowScene && isSceneInitialized[nc][sc] && sc == Window::getSceneCount(static_cast<SceneID>(nc)) - 1)
					{
						scenes[nc][sc]->draw();
						scenes[nc][sc]->over();
					}
				}
			}
			break;
		}
		//always
		for (size_t nc{}; nc < static_cast<size_t>(SceneID::result); nc++)
		{
			for (size_t sc{}; sc < Window::getSceneCount(static_cast<SceneID>(nc)); sc++)
			{
				scenes[nc][sc]->always();
			}
		}
	}
	glfwTerminate();
	//end
	for (size_t nc{}; nc < static_cast<size_t>(SceneID::result); nc++)
	{
		for (size_t sc{}; sc < Window::getSceneCount(static_cast<SceneID>(nc)); sc++)
		{
			scenes[nc][sc]->end();
		}
	}
	status = 1;
	ShowCursor(true);
}
void Window::appendScene(Scene* scene)
{
	scenes[scene->getSceneID()].push_back(scene);
	isSceneInitialized[scene->getSceneID()].push_back(false);
}
void Window::changeScene(SceneID sceneID)
{
	nowScene = sceneID;
}
void Window::initScenes()
{
	scenes.clear();
	scenes.shrink_to_fit();
	scenes.resize(static_cast<size_t>(SceneID::result) + 1);
	isSceneInitialized.clear();
	isSceneInitialized.shrink_to_fit();
	isSceneInitialized.resize(static_cast<size_t>(SceneID::result) + 1);
}
// Getter
GLFWwindow* Window::getWindow() const { return window; };
bool Window::isKeyDown(int key) { return static_cast<bool>(glfwGetKey(window, key)); }
bool Window::isMouseButtonDown(int Button) { return static_cast<bool>(glfwGetMouseButton(window, Button)); }
char Window::getStatus() const { return status; }
SceneID Window::getNowScene() const { return nowScene; }
size_t Window::getSceneCount(SceneID sceneID) const { return scenes[sceneID].size(); }
