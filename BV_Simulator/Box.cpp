#include "StdAfx.h"
#include "Box.h"

using namespace irr;

Box::Box(scene::ISceneManager* smgr, float x, float y, float z)
{
	mesh = smgr->getMesh("../models//box/box.mesh");
	node = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 128);
	node->setPosition(core::vector3df(x,y,z));
	core::vector3df nodePosition = node->getPosition();
	node->setScale(core::vector3df(10,10,10));
}

Box::~Box(void)
{
}

void Box::update(long time){

}