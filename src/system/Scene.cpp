#include "Scene.hpp"

/* class Scene */
// Constructor
Scene::Scene()
{
	sceneID = SceneID::boot;
}
Scene::Scene(SceneID sceneID)
{
	this->sceneID = sceneID;
}
// Methods
void Scene::once() {}
void Scene::init() {}
void Scene::draw() {}
void Scene::over() {}
void Scene::always() {};
void Scene::final() {}
void Scene::end() {}
// Getter
SceneID Scene::getSceneID() const { return sceneID; }


/* class Texture */
Texture::Texture(){}
Texture::Texture(const char* fileName)
{
	strcpy_s(this->fileName, sizeof(this->fileName), fileName);
}
// Destructor
Texture::~Texture()
{
	img.release();
	glDeleteTextures(1, &texture);
}
// Methods
bool Texture::load()
{
	static int count{};
	img = cv::imread(fileName, cv::IMREAD_UNCHANGED);
	if (img.empty())
		return false;
	width = img.cols;
	height = img.rows;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	return true;
}
bool Texture::imread()
{
	static int count{};
	img = cv::imread(fileName, cv::IMREAD_UNCHANGED);
	if (img.empty())
		return false;
	width = img.cols;
	height = img.rows;
	return true;
}
void Texture::send()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void Texture::free()
{
	img.release();
	glDeleteTextures(1, &texture);
}
// Getter
GLuint Texture::getTexture() const { return texture; }
int Texture::getWidth() const { return width; }
int Texture::getHeight() const { return height; }


/* class Text */
// Constructor
Text::Text(const char* text, const char* fontName, int fontSize)
{
	MultiByteToWideChar(CP_ACP, 0, text, strlen(text), this->text, strlen(text));
	MultiByteToWideChar(CP_ACP, 0, fontName, strlen(fontName), this->fontName, strlen(fontName));
	this->fontSize = fontSize;
}
Text::Text(const wchar_t* text, const wchar_t* fontName, int fontSize)
{
	lstrcpy(this->text, text);
	lstrcpy(this->fontName, fontName);
	this->fontSize = fontSize;
}
Text::Text(const char* text, HFONT* font)
{
	MultiByteToWideChar(CP_ACP, 0, text, strlen(text), this->text, strlen(text));
	this->font = font;
}
Text::Text(const wchar_t* text, HFONT* font)
{
	lstrcpy(this->text, text);
	this->font = font;
}
// Destructor
Text::~Text()
{
	img.release();
	glDeleteTextures(1, &texture);
	if (font == nullptr)
		DeleteObject(sFont);
	DeleteDC(hDC);
	DeleteObject(hBitmap);
}
// Method
void Text::create(uchar R, uchar G, uchar B)
{
	HFONT sFont{};
	HDC hDC = CreateCompatibleDC(NULL);
	SIZE size{};
	BITMAPINFO bminfo{};
	BITMAPINFOHEADER bmiHeader{};
	HBITMAP hBitmap{};
	LPVOID lp{};
	BITMAP bitmap{};
	if (font == nullptr)
		sFont = CreateFontW(fontSize, 0, 0, 0, 0, false, false, false, SHIFTJIS_CHARSET, OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 0, fontName);
	else
		sFont = *font;
	SelectObject(hDC, sFont);
	GetTextExtentPoint32W(hDC, text, lstrlenW(text), &size);
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth = size.cx;
	bmiHeader.biHeight = size.cy;
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = 32;
	bmiHeader.biCompression = BI_RGB;
	bmiHeader.biSizeImage = 0;
	bmiHeader.biClrUsed = 0;
	bmiHeader.biXPelsPerMeter = 1;
	bmiHeader.biYPelsPerMeter = 1;
	bmiHeader.biClrImportant = 0;
	bminfo.bmiHeader = bmiHeader;
	width = size.cx;
	height = size.cy;
	hBitmap = CreateDIBSection(hDC, &bminfo, DIB_RGB_COLORS, &lp, NULL, NULL);
	if (hBitmap == NULL)
	{
		if (font == nullptr)
			DeleteObject(sFont);
		DeleteDC(hDC);
		return;
	}
	SelectObject(hDC, hBitmap);
	TextOut(hDC, 0, 0, text, lstrlenW(text));
	GetObject(hBitmap, sizeof(bitmap), &bitmap);
	img = cv::Mat(bitmap.bmHeight, bitmap.bmWidth, CV_8UC4, (void*)bitmap.bmBits);
	cv::flip(img, img, 0);
	for (int x = 0; x < img.cols; x++)
	{
		for (int y = 0; y < img.rows; y++)
		{
			cv::Vec4b& color = img.at<cv::Vec4b>(y, x);				
			color[3] = ((16581375 - color[0] * color[1] * color[2]) / 16581375.0) * 255;
			color[0] = 0;
			color[1] = 0;
			color[2] = 0;
		}
	}
	if (!(R == 0 && G == 0 && B == 0))
	{
		for (int x = 0; x < img.cols; x++)
		{
			for (int y = 0; y < img.rows; y++)
			{
				cv::Vec4b& color = img.at<cv::Vec4b>(y, x);
				if (color[3] > 0)
				{
					color[0] = B;
					color[1] = G;
					color[2] = R;
				}
			}
		}
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (font == nullptr)
		DeleteObject(sFont);
	DeleteDC(hDC);
	DeleteObject(hBitmap);
}
void Text::set(uchar R, uchar G, uchar B)
{
	hDC = CreateCompatibleDC(NULL);
	SIZE size{};
	BITMAPINFO bminfo{};
	BITMAPINFOHEADER bmiHeader{};
	LPVOID lp{};
	BITMAP bitmap{};
	if (font == nullptr)
		sFont = CreateFontW(fontSize, 0, 0, 0, 0, false, false, false, SHIFTJIS_CHARSET, OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 0, fontName);
	else
		sFont = *font;
	SelectObject(hDC, sFont);
	GetTextExtentPoint32W(hDC, text, lstrlenW(text), &size);
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth = size.cx;
	bmiHeader.biHeight = size.cy;
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = 32;
	bmiHeader.biCompression = BI_RGB;
	bmiHeader.biSizeImage = 0;
	bmiHeader.biClrUsed = 0;
	bmiHeader.biXPelsPerMeter = 1;
	bmiHeader.biYPelsPerMeter = 1;
	bmiHeader.biClrImportant = 0;
	bminfo.bmiHeader = bmiHeader;
	width = size.cx;
	height = size.cy;
	hBitmap = CreateDIBSection(hDC, &bminfo, DIB_RGB_COLORS, &lp, NULL, NULL);
	if (hBitmap == NULL)
	{
		if (font == nullptr)
			DeleteObject(sFont);
		DeleteDC(hDC);
		return;
	}
	SelectObject(hDC, hBitmap);
	TextOut(hDC, 0, 0, text, lstrlenW(text));
	GetObject(hBitmap, sizeof(bitmap), &bitmap);
	img = cv::Mat(bitmap.bmHeight, bitmap.bmWidth, CV_8UC4, (void*)bitmap.bmBits);
	cv::flip(img, img, 0);
	for (int x = 0; x < img.cols; x++)
	{
		for (int y = 0; y < img.rows; y++)
		{
			cv::Vec4b& color = img.at<cv::Vec4b>(y, x);
			color[3] = ((16581375 - color[0] * color[1] * color[2]) / 16581375.0) * 255;
			color[0] = 0;
			color[1] = 0;
			color[2] = 0;
		}
	}
	if (!(R == 0 && G == 0 && B == 0))
	{
		for (int x = 0; x < img.cols; x++)
		{
			for (int y = 0; y < img.rows; y++)
			{
				cv::Vec4b& color = img.at<cv::Vec4b>(y, x);
				if (color[3] > 0)
				{
					color[0] = B;
					color[1] = G;
					color[2] = R;
				}
			}
		}
	}
}
void Text::send()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (font == nullptr)
		DeleteObject(sFont);
	DeleteDC(hDC);
	DeleteObject(hBitmap);
}
void Text::free()
{
	img.release();
	glDeleteTextures(1, &texture);
	if (font == nullptr)
		DeleteObject(sFont);
	DeleteDC(hDC);
	DeleteObject(hBitmap);
}
// Getter
GLuint Text::getTexture() const { return texture; }
int Text::getWidth() const { return width; }
int Text::getHeight() const { return height; }


/** class Sound */
void Sound::setUp(int* argc, char* argv[])
{
	static ALboolean __ALUTINIT{ AL_FALSE };
	if (__ALUTINIT == AL_FALSE)
	{
		if ((__ALUTINIT = alutInit(argc, argv)) == AL_FALSE)
			Error::error("Alut‚Ì‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
	}
}
void Sound::End() { alutExit(); }
// Constructor
Sound::Sound() {}
Sound::Sound(const char* fileName)
{
	strcpy_s(this->fileName, sizeof(this->fileName), fileName);
}
// Destructor
Sound::~Sound()
{
	alDeleteSources(1, &sound);
	alDeleteBuffers(1, &buffer);
	buffer = 0;
	sound = 0;
}
bool Sound::load()
{
	alGenBuffers(1, &buffer);
	buffer = alutCreateBufferFromFile(fileName);
	alGenSources(1, &sound);
	if (sound == NULL)
		return false;
	alSourcei(sound, AL_BUFFER, buffer);
	return true;
}
void Sound::free()
{
	alDeleteSources(1, &sound);
	alDeleteBuffers(1, &buffer);
	buffer = 0;
	sound = 0;
}
void Sound::play() const { alSourcePlay(sound); }
void Sound::pause() const { alSourcePause(sound); }
void Sound::stop() const { alSourceStop(sound); }
void Sound::seek(ALdouble sec) const { alSourcef(sound, AL_SEC_OFFSET, sec); }
bool Sound::isPlaying() const
{
	ALint get{};
	alGetSourcei(sound, AL_SOURCE_STATE, &get);
	if (get == AL_PLAYING)
		return true;
	return false;
}
void Sound::setStatus(ALenum param, ALint value) const{ alSourcei(sound, param, value); }
void Sound::setStatus(ALenum param, ALdouble value) const { alSourcef(sound, param, value); }
void Sound::setStatus(ALenum param, ALfloat value) const { alSourcef(sound, param, value); }
void Sound::getStatus(ALenum param, ALint *value) const { alGetSourcei(sound, param, value); }
void Sound::getStatus(ALenum param, ALfloat *value) const { alGetSourcef(sound, param, value); }


/* class Draw */
void Draw::drawRect(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	glBindTexture(GL_TEXTURE_2D, NULL);
	glRectd(x1, y1, x2, y2);
}
void Draw::drawRectC(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	glBindTexture(GL_TEXTURE_2D, NULL);
	glRectd(2 * x1 / __WIDTH - 1, 1 - y1 / 540, 2 * x2 / __WIDTH - 1, 1 - y2 / 540);
}
void Draw::drawTexture(GLdouble x, GLdouble y, Texture* texture)
{
	GLdouble m1 = static_cast<double>(texture->getWidth()) / (__WIDTH / 2.0) - 1;
	GLdouble m2 = static_cast<double>(texture->getHeight()) / (__HEIGHT / 2.0) - 1;
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex2d(x * 2 + 1 * m1, -y * 2 + 1);
	glTexCoord2f(1, 1);
	glVertex2d(x * 2 + 1 * m1, -y * 2 - 1 * m2);
	glTexCoord2f(0, 1);
	glVertex2d(x * 2 - 1, -y * 2 - 1 * m2);
	glTexCoord2f(0, 0);
	glVertex2d(x * 2 - 1, -y * 2 + 1);
	glEnd();
}
void Draw::drawTexture(GLdouble x, GLdouble y, Text* text)
{
	GLdouble m1 = static_cast<double>(text->getWidth()) / (__WIDTH / 2.0) - 1;
	GLdouble m2 = static_cast<double>(text->getHeight()) / (__HEIGHT / 2.0) - 1;
	glBindTexture(GL_TEXTURE_2D, text->getTexture());
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex2d(x * 2 + 1 * m1, -y * 2 + 1);
	glTexCoord2f(1, 1);
	glVertex2d(x * 2 + 1 * m1, -y * 2 - 1 * m2);
	glTexCoord2f(0, 1);
	glVertex2d(x * 2 - 1, -y * 2 - 1 * m2);
	glTexCoord2f(0, 0);
	glVertex2d(x * 2 - 1, -y * 2 + 1);
	glEnd();
}
void Draw::drawTextureC(GLdouble x, GLdouble y, Texture* texture)
{
	GLdouble x1 = 1.0 * x / __WIDTH;
	GLdouble y1 = 1.0 * y / __HEIGHT;
	GLdouble m1 = static_cast<double>(texture->getWidth()) / (__WIDTH / 2.0) - 1;
	GLdouble m2 = static_cast<double>(texture->getHeight()) / (__HEIGHT / 2.0) - 1;
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex2d(x1 * 2 + 1 * m1, -y1 * 2 + 1);
	glTexCoord2f(1, 1);
	glVertex2d(x1 * 2 + 1 * m1, -y1 * 2 - 1 * m2);
	glTexCoord2f(0, 1);
	glVertex2d(x1 * 2 - 1, -y1 * 2 - 1 * m2);
	glTexCoord2f(0, 0);
	glVertex2d(x1 * 2 - 1, -y1 * 2 + 1);
	glEnd();
}
void Draw::drawTextureC(GLdouble x, GLdouble y, Text* text)
{
	GLdouble x1 = 1.0 * x / __WIDTH;
	GLdouble y1 = 1.0 * y / __HEIGHT;
	GLdouble m1 = static_cast<double>(text->getWidth()) / (__WIDTH / 2.0) - 1;
	GLdouble m2 = static_cast<double>(text->getHeight()) / (__HEIGHT / 2.0) - 1;
	glBindTexture(GL_TEXTURE_2D, text->getTexture());
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex2d(x1 * 2 + 1 * m1, -y1 * 2 + 1);
	glTexCoord2f(1, 1);
	glVertex2d(x1 * 2 + 1 * m1, -y1 * 2 - 1 * m2);
	glTexCoord2f(0, 1);
	glVertex2d(x1 * 2 - 1, -y1 * 2 - 1 * m2);
	glTexCoord2f(0, 0);
	glVertex2d(x1 * 2 - 1, -y1 * 2 + 1);
	glEnd();
}
void Draw::drawRectTexture(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, Texture* texture)
{
	GLdouble x3 = 1.0 * x1 / 1.0;
	GLdouble y3 = 1.0 * y1 / 1.0;
	GLdouble x4 = 1.0 * x2 / 1.0;
	GLdouble y4 = 1.0 * y2 / 1.0;
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex2d(x4 * 2 - 1, -y3 * 2 + 1);
	glTexCoord2f(1, 1);
	glVertex2d(x4 * 2 - 1, -y4 * 2 + 1);
	glTexCoord2f(0, 1);
	glVertex2d(x3 * 2 - 1, -y4 * 2 + 1);
	glTexCoord2f(0, 0);
	glVertex2d(x3 * 2 - 1, -y3 * 2 + 1);
	glEnd();
}
void Draw::drawRectTexture(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, Text* text)
{
	GLdouble x3 = 1.0 * x1 / 1.0;
	GLdouble y3 = 1.0 * y1 / 1.0;
	GLdouble x4 = 1.0 * x2 / 1.0;
	GLdouble y4 = 1.0 * y2 / 1.0;
	glBindTexture(GL_TEXTURE_2D, text->getTexture());
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex2d(x4 * 2 - 1, -y3 * 2 + 1);
	glTexCoord2f(1, 1);
	glVertex2d(x4 * 2 - 1, -y4 * 2 + 1);
	glTexCoord2f(0, 1);
	glVertex2d(x3 * 2 - 1, -y4 * 2 + 1);
	glTexCoord2f(0, 0);
	glVertex2d(x3 * 2 - 1, -y3 * 2 + 1);
	glEnd();
}
void Draw::drawRectTextureC(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, Texture* texture)
{
	GLdouble x3 = 1.0 * x1 / __WIDTH;
	GLdouble y3 = 1.0 * y1 / __HEIGHT;
	GLdouble x4 = 1.0 * x2 / __WIDTH;
	GLdouble y4 = 1.0 * y2 / __HEIGHT;
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex2d(x4 * 2 - 1, -y3 * 2 + 1);
	glTexCoord2f(1, 1);
	glVertex2d(x4 * 2 - 1, -y4 * 2 + 1);
	glTexCoord2f(0, 1);
	glVertex2d(x3 * 2 - 1, -y4 * 2 + 1);
	glTexCoord2f(0, 0);
	glVertex2d(x3 * 2 - 1, -y3 * 2 + 1);
	glEnd();
}
void Draw::drawRectTextureC(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, Text* text)
{
	GLdouble x3 = 1.0 * x1 / __WIDTH;
	GLdouble y3 = 1.0 * y1 / __HEIGHT;
	GLdouble x4 = 1.0 * x2 / __WIDTH;
	GLdouble y4 = 1.0 * y2 / __HEIGHT;
	glBindTexture(GL_TEXTURE_2D, text->getTexture());
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex2d(x4 * 2 - 1, -y3 * 2 + 1);
	glTexCoord2f(1, 1);
	glVertex2d(x4 * 2 - 1, -y4 * 2 + 1);
	glTexCoord2f(0, 1);
	glVertex2d(x3 * 2 - 1, -y4 * 2 + 1);
	glTexCoord2f(0, 0);
	glVertex2d(x3 * 2 - 1, -y3 * 2 + 1);
	glEnd();
}