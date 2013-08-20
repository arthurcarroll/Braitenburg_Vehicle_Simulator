#pragma once
#include "BV_Object.h"
#include <vector>
class Stimuli : public BV_Object
{
public:
	Stimuli(irr::scene::ISceneManager* smgr, float x, float y, float z ,std::string n, float strength);
	~Stimuli(void);
	void update(long time);
	std::string name;
	float strength;
	
};
