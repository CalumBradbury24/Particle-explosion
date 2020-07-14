
#define SDL_MAIN_HANDLED
#include <iostream>
#include "SDL2/SDL.h"
#include <stdio.h>
#include <cstring>
#include "ScreenDisplay.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Group.h"
#include "Particles.h"
using namespace std;

int main() {


	srand(time(NULL)); //Seed random number generator to produce diff sequence of numbers every time main runs

	ScreenDisplay screen;

	if (screen.init() == false) {
		cout << "Error initialising SDL" << endl;
	}

	Group group;

	while (true) {
		//update state of particles

		//draw particles

		int runTime = SDL_GetTicks(); //Gets number of milliseconds since the program started
		//screen.clear();
		group.update(runTime);

		unsigned char green = (unsigned char) ((1 + sin(runTime * 0.001)) * 128); //0-255 (unsigned char can store 255 max, so if green was greater than 255 it would map to 255(the largest number for green))
		unsigned char red = (unsigned char) ((1 + sin(runTime * 0.002)) * 128); //0-255
		unsigned char blue = (unsigned char) ((1 + sin(runTime * 0.003)) * 128); //0-255

		//const pointer to a particle that's const
		const Particles *const pParticles = group.getParticles();

		for (int i = 0; i < Group::NPARTICLES; i++) {
			Particles particle = pParticles[i];
			//+1 so range is 0-2 rather than -1-+1
			int x = (particle.m_xpos + 1) * ScreenDisplay::SCREEN_WIDTH / 2; //Use SCREEN_WIDTH from Screen class
			int y = particle.m_ypos * ScreenDisplay::SCREEN_WIDTH / 2 + ScreenDisplay::SCREEN_HEIGHT/2;//+half screen height to position y axis in the middle

			screen.setPixel(x, y, red, green, blue);

		}

		screen.boxBlur();//Screen is not cleared, blur the trails of particles as they move across the screen

		//Draw the screen
		screen.update();

		//check for messages/events
		if (screen.processEvents() == false) {
			break; //Break out of loop when window is closed
		}
	}

	screen.close();
	return 0;
}
