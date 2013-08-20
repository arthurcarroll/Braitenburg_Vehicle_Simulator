#pragma once
#include "BV_Object.h"
class GroundPlane : public BV_Object
{
public:
	GroundPlane(irr::scene::ISceneManager* smgr, float x, float y, float z, int ID);
	~GroundPlane(void);
	void update(long time);

};
