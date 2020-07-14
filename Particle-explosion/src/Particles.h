/*
 * Particle.h
 *
 *  Created on: 13 Jul 2020
 *      Author: calum bradbury
 */

#ifndef PARTICLES_H_
#define PARTICLES_H_

namespace std {
//Struct member variables are public by default (private in class) - the only difference between class and struct
struct Particles {
	double m_xpos, m_ypos;//Positions of particle -Break encapsulation by using public data members but more efficient in this case because of how many pixels we are dealing with modifying

	double m_speed; //How fast a particle is moving
	double m_direction;//Angle between 0-360 degrees particle is moving in

	Particles();
	void update(int);//Update position of particle to mimic movement
	virtual ~Particles();



};


} /* namespace std */

#endif /* PARTICLES_H_ */
