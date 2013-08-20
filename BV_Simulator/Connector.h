#pragma once
#include "Motor.h"
#include "Sensor.h"
#include "StdAfx.h"

class Connector
{
public:
	Connector(Motor* act, Sensor* sen, bool pos);
	~Connector(void);
	Motor* actuator;
	Sensor* sensor;
	bool positive;
};
