#include "StdAfx.h"
#include "Motor.h"

Motor::Motor(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode *Pnode, irr::core::vector3df pos, std::string file, std::string side)
{
	mesh= smgr->getMesh(file.c_str());
	node = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 512);
	node->setPosition(irr::core::vector3df(pos));
	Pnode->addChild(node);
	this->side = side;
}

Motor::~Motor(void)
{
}
