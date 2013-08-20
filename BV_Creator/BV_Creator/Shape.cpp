#include "stdafx.h"
#include "Shape.h"

Shape::Shape(void)
{
}
Shape::Shape(vector<LineSegment> s, Point2D point, string n)
{
	this->location=point;
	this->shape=s; 
	this->name=n;
	this->vehicleName = "";
}

Shape::Shape(Point2D point, string n , string file)
{
	this->location=point;
	this->name=n;
	this->vehicleName = file;
}
Shape::~Shape(void)
{
}

vector<LineSegment> Shape::getShape(){
	return shape;
}

int  Shape::getPointNumber(){
	return this->location.pointNumber;
}