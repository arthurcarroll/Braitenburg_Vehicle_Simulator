#pragma once
#include "LineSegment.h"
#include "Point2D.h"
#include <vector>

using namespace std;

class Shape
{
public:
	Point2D location;
	vector<LineSegment> shape;
	string name;
	string vehicleName;
	//void setShape(vector<LineSegment> s);
	vector<LineSegment> getShape();
	Shape(void);
	Shape(vector<LineSegment> s, Point2D point, string n);
	Shape(Point2D point, string name, string file);
	~Shape(void);
	int getPointNumber();
};

