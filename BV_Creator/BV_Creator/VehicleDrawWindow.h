#ifndef _a_h_included_
#define _a_h_included_
#pragma once
#include "Point2D.h"
#include "Controller.h"
#include "Shape.h"
#include "LineSegment.h"
#include <vector>


using namespace std;

class Controller;

enum {
	ERROR_ARGS = 1, 
	ERROR_XERCES_INIT,
	ERROR_PARSE,
	ERROR_EMPTY_DOCUMENT
};


class VehicleDrawWindow : public Fl_Widget
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
	bool connecting;
	bool notConnector;
	bool firstPoint;
	Point2D prevPoint;
	int pointNumber;
	string placing;
	string prevPlacing;
    int radius;
	string file;
	int numPoints;
	int handle(int event);
	void draw(void);
	void addVertPoints(int xStart, int yStart, int yTick, int side);
	void addHorizPoints(int xStart, int yStart, int xTick, int side);
	int checkPoint(int pointX, int pointY);
	bool inMargin(int point1, int point2, int pointMargin);
	void drawPoints(vector<Point2D> points);
	void resetPoints(vector<Point2D> &points);
	VehicleDrawWindow(Controller m, int x,int y,int w,int h,const char *lab=0);
	~VehicleDrawWindow(void);
	void addShape(Point2D p);
	

};

#endif