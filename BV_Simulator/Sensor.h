#pragma once
#include "StdAfx.h"
#include "BV_Object.h"

class Sensor : public BV_Object
{
public:
	Sensor(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode *Pnode, irr::core::vector3df pos, std::string file, std::string stim,std::string s);
	~Sensor(void);
	std::string stimuli;
	std::string side;
};
