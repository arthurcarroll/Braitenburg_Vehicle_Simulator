#include "StdAfx.h"
#include "Sensor.h"

Sensor::Sensor(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode *Pnode, irr::core::vector3df pos, std::string file, std::string stim,std::string s)
{
	mesh= smgr->getMesh(file.c_str());
	node = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 512);
	node->setPosition(pos);
	Pnode->addChild(node);
	this->stimuli = stim;
	this->side = s;
}

Sensor::~Sensor(void)
{
}
