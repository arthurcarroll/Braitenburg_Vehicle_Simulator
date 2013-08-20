#include "StdAfx.h"
#include "Stimuli.h"

using namespace irr;

Stimuli::Stimuli(scene::ISceneManager* smgr, float x, float y, float z, std::string n, float strength)
{
	float constant = .5;
	mesh = smgr->getMesh("../models/light/light.mesh");
	node = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 512);
	node->setPosition(core::vector3df(x,y,z));
	core::vector3df nodePosition = node->getPosition();
	node->setScale(core::vector3df(strength*constant,strength*constant,strength*constant));
	this->name = n;
	this->strength  = strength;
	
}

Stimuli::~Stimuli(void)
{
}

void Stimuli::update(long time){

}