/*
 * Swarm.h
 *
 *  Created on: 13 Jul 2020
 *      Author: calum bradbury
 */

#ifndef GROUP_H_
#define GROUP_H_

#include "Particles.h"

namespace std {

class Group {
public:
	const static int NPARTICLES = 5000;//Public for use elsewhere outside of swarm class

	Group();
	//Returns a particle pointer that can't be changed
	const Particles* const getParticles(){return m_pParticles;}; //Implemented inline because it is a small function so not needed in cpp file
	void update(int);
	virtual ~Group();

private:
	Particles* m_pParticles;//Pointer
	int lastTime;
};

} /* namespace std */

#endif /* GROUP_H_ */
