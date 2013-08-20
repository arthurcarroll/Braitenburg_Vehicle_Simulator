#pragma once
#include "StdAfx.h"
#include "BV_Object.h"
#include "SAppContext.h"
#include "Stimuli.h"
#include "Sensor.h"
#include "Motor.h"
#include "Connector.h"
#include <vector>
#include <string>


class Vehicle : public BV_Object
{
public:
	Vehicle(irr::scene::ISceneManager* smgr, float x, float y, float z);
	~Vehicle(void);
	void update(irr::u32 time, std::vector<Stimuli> stims);
	void load(irr::scene::ISceneManager* smgr);
	void move(irr::scene::ISceneNode *node, irr::core::vector3df vel); 
	
	std::vector<Sensor*> sensors;
	std::vector<Motor*> motors;
	std::vector<Connector*> connectors;
	float prevTime;
	bool firstUpdate;
	float lastRotation;

	

	
};
