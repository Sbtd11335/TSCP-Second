#include "Window.hpp"

int Window::__GLFWINIT = glfwInit();

// Constructor
Window::Window()
{
	width = 640;
	height = 480;
	strcpy_s(title, sizeof(title), "");
}
Window::Window(const char* title)
{
	width = 640;
	height = 480;
	strcpy_s(this->title, sizeof(this->title), title);
}
Window::Window(int width, int height)
{
	this->width = width;
	this->height = height;
	strcpy_s(title, sizeof(title), "");
}
Window::Window(int width, int height, const char* title)
{
	this->width = width;
	this->height = height;
	strcpy_s(this->title, sizeof(this->title), title);
}
// Methods
void Window::create(bool fullScreen, bool vSync)
{
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
	status = 0;
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
		//draw

		//over
		
	}
	glfwTerminate();
	status = 1;
	ShowCursor(true);
}
// Getter
GLFWwindow* Window::getWindow() const { return window; };
bool Window::isKeyDown(int key) { return static_cast<bool>(glfwGetKey(window, key)); }
bool Window::isMouseButtonDown(int Button) { return static_cast<bool>(glfwGetMouseButton(window, Button)); }
char Window::getStatus() const { return status; }