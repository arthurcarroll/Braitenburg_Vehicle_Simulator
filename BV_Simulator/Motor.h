#pragma once
#include "StdAfx.h"
#include "BV_Object.h"

class Motor : public BV_Object
{
public:
	std::string side;
	Motor(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode *Pnode, irr::core::vector3df pos, std::string file, std::string side);
	~Motor(void);

};
