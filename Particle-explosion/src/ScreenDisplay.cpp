
/*
 * Screen.cpp
 *
 *  Created on: 10 Jul 2020
 *      Author: calum bradbury
 */
#define SDL_MAIN_HANDLED
#include "ScreenDisplay.h"
#include "SDL2/SDL.h"
#include <stdio.h>
#include <cstring>
#include <iostream>
namespace std {

ScreenDisplay::ScreenDisplay():
		// TODO Auto-generated constructor stub
		m_window(NULL), //Member variables
		m_renderer(NULL), m_texture(NULL), m_buffer1(NULL),m_buffer2(NULL) {
}

bool ScreenDisplay::init() {

	m_window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL2 init failed: %s\n", SDL_GetError());
		return false;
	}
	cout << "SDL2 init successful";

	m_window = SDL_CreateWindow("Particle explosion",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN //Create normal unaltered window
			);

	if (m_window == NULL) { //If window can't be created
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_renderer == NULL) {
		cout << "could not create renderer" << endl;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	if (m_texture == NULL) {
		cout << "could not create texture" << endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	//Allocate memory for screen
	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; //SDL defined int of 32bits
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; //SDL defined int of 32bits
	//Write pixel information into buffer
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	return true;
}
bool ScreenDisplay::processEvents() {
	SDL_Event event;
	//Close the screen when the cross is clicked
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) { //SDL_QUIT event is generated(is true) when user clicks on close button of last existing window.
			return false; //Break out of while loop
		}
	}
	return true;
}

void ScreenDisplay::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

	if(x <0 || x >= SCREEN_WIDTH || y<0 || y >= SCREEN_HEIGHT){//Don't plot pixels off of the screen
		return;
	}

	Uint32 colour = 0; //32 bit unsigned int on all platforms (defined by SDL)
//RGBA
	colour += red; //Red value
	colour <<= 8; //Bit shift 8 to left
	colour += green;
	colour <<= 8;
	colour += blue;
	colour <<= 8;
	colour += 0xFF; //Alpha (opacity FF=1)

//(y*SCREEN_WIDTH) gets correct row, e.g if want to go 10 rows down (y=10),
//each row has width=SCREEN_WIDTH so we have 10 rows of size SCREEN_WIDTH to go down
//to get to row 10. Then add x(column value) to move to the right by x value to get to right pixel

	m_buffer1[(y * SCREEN_WIDTH) + x] = colour; //Set value in buffer
}

void ScreenDisplay::update() {
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL); //copy texture to renderer
	SDL_RenderPresent(m_renderer); //Present renderer to the window
}
//blur pixels so particles leave blurred trace behind them
void ScreenDisplay::boxBlur(){
	//Calculate new screen of pixels with blurred values using second buffer
//Swap buffers so pixel info is in buffer 2 and we are drawing to buffer 1
	Uint32 *temp = m_buffer1;

	m_buffer1 = m_buffer2;
	m_buffer2 = temp;
	//iterate through all pixels
	for(int y =0; y<SCREEN_HEIGHT; y++){
		for(int x=0; x<SCREEN_WIDTH; x++){

			int redTotal=0;
			int greenTotal=0;
			int blueTotal=0;


			for(int row=-1;row<=1;row++){
				for(int col=-1; col<=1; col++){
					int currentX= x + col;
					int currentY= y+row;
					//Ignore pixels off screen
					if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >=0 && currentY < SCREEN_HEIGHT){
						Uint32 colour = m_buffer2[currentY*SCREEN_WIDTH + currentX];
						Uint8 red=colour >> 24;//Right shift colour to get red value
						Uint8 green = colour >> 16;//Shift right 16 bits for green
						Uint8 blue = colour >> 8;//Shift 8 bits

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}
			Uint8 red = redTotal/9;
			Uint8 green = greenTotal/9;
			Uint8 blue = blueTotal/9;

			setPixel(x, y, red, green, blue);
		}
	}
}

void ScreenDisplay::close() {
	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
ScreenDisplay::~ScreenDisplay() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
