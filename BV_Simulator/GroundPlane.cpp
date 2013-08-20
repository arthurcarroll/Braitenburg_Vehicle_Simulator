#include "StdAfx.h"
#include "GroundPlane.h"

using namespace irr;

GroundPlane::GroundPlane(scene::ISceneManager* smgr, float x, float y, float z, int ID)
{
	
	mesh = smgr->getMesh("../models/groundGraph/groundGraph.mesh");
	node = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, ID, 512);
	node->setPosition(core::vector3df(x,y,z));
	core::vector3df nodePosition = node->getPosition();
	node->setScale(core::vector3df(10,10,10));
}

GroundPlane::~GroundPlane(void)
{
}

void GroundPlane::update(long time){

}