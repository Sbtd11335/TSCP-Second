#ifndef __TSCP_SYSTEM_SCENE_HPP
#	define __TSCP_SYSTEM_SCENE_HPP

#	pragma comment(lib, "glfw3.lib")
#	pragma comment(lib, "opengl32.lib")
#	pragma comment(lib, "OpenAL32.lib")
#	pragma comment(lib,"msimg32.lib")
#	ifdef _DEBUG
#		pragma comment(lib, "opencv_world490d.lib")
#	else
#		pragma comment(lib, "opencv_world490.lib")
#	endif

#	ifdef _DEBUG
#		pragma comment(lib, "alut_debug.lib")
#	else
#		pragma comment(lib, "alut.lib")
#	endif


#	include "../Macro.hpp"
#	include "Error.hpp"
#	include <opencv2/opencv.hpp>
#	include <GLFW/glfw3.h>
#	include <stdio.h>
#	include <string.h>
#	include <AL/alut.h>
#	include <iostream>
#	include <Windows.h>

enum SceneID {
	boot,
	title,
	entry,
	selectSong,
	playSong,
	result //Last
};

class Scene {
protected:
	SceneID sceneID{ SceneID::boot };

public:
	// Constructor
	Scene();
	Scene(SceneID sceneID);
	// Methods
	virtual void once();
	virtual void init();
	virtual void draw();
	virtual void over();
	virtual void always();
	virtual void final();
	virtual void end();
	// Getter
	SceneID getSceneID() const;
};

class Texture {
private:
	char fileName[__FILE_BUFFERSIZE]{};
	cv::Mat img{};
	GLuint texture{};
	int width{}, height{};

public:
	Texture();
	Texture(const char* fileName);
	~Texture();
	bool imread();
	void send();
	bool load();
	void free();
	GLuint getTexture() const;
	int getWidth() const;
	int getHeight() const;

};

class Text {
private:
	wchar_t text[256]{};
	wchar_t fontName[64]{};
	int width{}, height{}, fontSize{};
	cv::Mat img{};
	GLuint texture{};
	HFONT* font{ nullptr };
	HFONT sFont{};
	HDC hDC{};
	HBITMAP hBitmap{};
public:
	// Constructor
	Text(const char* text, const char* font, int fontSize);
	Text(const wchar_t* text, const wchar_t* font, int fontSize);
	Text(const char* text, HFONT* font);
	Text(const wchar_t* text, HFONT* font);
	// Destructor
	~Text();
	// Method
	void create(uchar R = 0, uchar G = 0, uchar B = 0);
	void set(uchar R = 0, uchar G = 0, uchar B = 0);
	void send();
	void free();
	// Getter
	GLuint getTexture() const;
	int getWidth() const;
	int getHeight() const;
};

class Sound {
private:
	char fileName[__FILE_BUFFERSIZE]{};
	ALuint buffer{}, sound{};

public:
	static void setUp(int* argc, char* argv[]);
	static void End();
	// Constructor
	Sound();
	Sound(const char* fileName);
	// Destructor
	~Sound();
	// Methods
	bool load();
	void free();
	void play() const;
	void pause() const;
	void stop() const;
	void seek(ALdouble sec) const;
	bool isPlaying() const;
	void setStatus(ALenum param, ALint value) const;
	void setStatus(ALenum param, ALdouble value) const;
	void setStatus(ALenum param, ALfloat value) const;
	void getStatus(ALenum param, ALint* value) const;
	void getStatus(ALenum param, ALfloat* value) const;
	template<typename Type>Type getStatusd(ALenum param) const
	{
		Type get{};
		alGetSourcef(sound, param, &get);
		return get;
	}

};

class Draw {
public:
	static void drawRect(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	static void drawRectC(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	static void drawTexture(GLdouble x, GLdouble y, Texture* texture);
	static void drawTexture(GLdouble x, GLdouble y, Text* text);
	static void drawTextureC(GLdouble x, GLdouble y, Texture* texture);
	static void drawTextureC(GLdouble x, GLdouble y, Text* text);
	static void drawRectTexture(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, Texture* texture);
	static void drawRectTexture(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, Text* text);
	static void drawRectTextureC(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, Texture* texture);
	static void drawRectTextureC(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, Text* text);

};
#endif