#include"Mod.hpp"

void __INITIALIZE()
{

}
Boot* __SCENE_BOOT()
{
	scene = new Boot;
	return scene;
}
Boot::Boot()
{
	this->sceneID = SceneID::boot;
}
void Boot::init()
{
	tex.load();
	main.load();
	main.setStatus(AL_LOOPING, AL_TRUE);
	main.play();
	text.create();
}
void Boot::final()
{
	tex.free();
	main.free();
	text.free();
}
void Boot::draw()
{
	glColor4d(1, 1, 1, 1);
	Draw::drawTexture(0, 0, &tex);
	Draw::drawTexture(0, 0, &text);
}
void Boot::over()
{
	if (overLay == false)
		return;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0, 0, 0, 0.5);
	glBindTexture(GL_TEXTURE_2D, NULL);
	Draw::drawRectC(0, 760, 450, 1080);
}
void Boot::end()
{
	final();
	delete scene;
}