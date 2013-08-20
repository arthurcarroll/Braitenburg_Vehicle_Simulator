#include "StdAfx.h"
#include "Connector.h"

Connector::Connector(Motor* act, Sensor* sen, bool pos)
{
	this->actuator = act;
	this->sensor = sen;
	this->positive = pos;
}

Connector::~Connector(void)
{
}
