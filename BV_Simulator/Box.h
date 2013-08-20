#pragma once
#include "BV_Object.h"
class Box : public BV_Object
{
public:
	Box(irr::scene::ISceneManager* smgr, float x, float y, float z);
	~Box(void);
	void update(long time);
};
