/*
 * Swarm.cpp
 *
 *  Created on: 13 Jul 2020
 *      Author: calum bradbury
 */

#include "Group.h"

#include "Particles.h"

namespace std {

Group::Group(): lastTime(0) {
	m_pParticles = new Particles[NPARTICLES];//particles array

}
void Group::update(int runTime){

	int interval = runTime - lastTime;//See how much time has elapsed since last time screen was updated

	for (int i=0; i < Group::NPARTICLES; i++){
		m_pParticles[i].update(interval);//Update each particle in particles cpp
	}

	lastTime = runTime;
}

Group::~Group() {
	delete[] m_pParticles;//Delete particles array
}

} /* namespace std */
