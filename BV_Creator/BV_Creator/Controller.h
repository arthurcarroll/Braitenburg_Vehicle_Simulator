#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <FL/Fl_Tabs.H>
#include "Shape.h"
#include "Point2D.h"
#include "GlobalNames.h"

class Controller
{
public:
	
	Controller(void);
	~Controller(void);
	void start();
	void save();
};

