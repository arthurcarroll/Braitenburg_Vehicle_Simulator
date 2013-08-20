#pragma once
#include "Controller.h"
#include <FL/Fl_draw.H>
#include "GlobalNames.h"

class Controller;

const int GRIDSPACING = 20;

class EnvironmentDrawWindow: public Fl_Widget
{
public:
	vector<Point2D> snapPoints;
	vector<Shape> shapes;
	int MouseX;
	int MouseY;
	int xPos;
	int yPos;
	int wPos;
	int hPos;
	int size;
	int margin;
	bool dragging;
	string placing;
	string nextFileName;
	bool connecting;
	void drawGrid();
	int handle(int event);
	int normalizeX(int x);
	int normalizeY(int y);
	void draw(void);
	EnvironmentDrawWindow(Controller m, int x,int y,int w,int h,const char *lab=0);
	~EnvironmentDrawWindow(void);
};
