/*
 * Particle.cpp
 *
 *  Created on: 13 Jul 2020
 *      Author: calum bradbury
 */

#include "Particles.h"

#include <stdlib.h> //rand()
#include <math.h>

namespace std {
//Initialisation using constructor initialisation list
//This list must be used for non-static const data members
Particles::Particles():m_xpos(0), m_ypos(0) {

	m_direction = (2* M_PI*rand())/RAND_MAX;
	m_speed = (0.0002*rand())/RAND_MAX;//Numerator is double for floating point division

}

void Particles::update(int interval){

	m_direction += interval*0.0004;
	double xspeed = m_speed*cos(m_direction);
	double yspeed = m_speed * sin(m_direction);

	m_xpos += xspeed * interval;//*interval ensures amount particle moves is proportional to time since last time particle moved
	m_ypos += yspeed * interval;//Makes movement speed more consistent regardless of speed of computer
}


Particles::~Particles() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
