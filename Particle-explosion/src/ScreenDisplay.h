/*
 * Screen.h
 *
 *  Created on: 10 Jul 2020
 *      Author: calum bradbury
 */

#ifndef SCREENDISPLAY_H_
#define SCREENDISPLAY_H_
#include "SDL2/SDL.h"
namespace std {

class ScreenDisplay {
public:
	ScreenDisplay();
	bool init(); //false if initialisation fails
	bool processEvents();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void close();
	void boxBlur();
	virtual ~ScreenDisplay();

	const static int SCREEN_WIDTH = 1000;
	const static int SCREEN_HEIGHT = 720;
private:
	SDL_Window *m_window;//Member variables
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer1;
	Uint32 *m_buffer2;
};

} /* namespace std */

#endif /* SCREENDISPLAY_H_ */
