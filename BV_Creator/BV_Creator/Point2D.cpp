#include "stdafx.h"
#include "Point2D.h"


Point2D::Point2D(void)
{
	this->x=0;
	this->y=0;
}
Point2D::Point2D(int X, int Y, int Color, int d, int number){
	this->pointNumber = number;
	this->x=X;
	this->y=Y;
	this->color=Color;
	this->direction=d;

}
Point2D::~Point2D(void)
{
}
int Point2D::getX(){
	return this->x;
}
int Point2D::getY(){
	return this->y;
}
int Point2D::getColor(){
	return this->color;
}
int Point2D::getDirection(){

	return this->direction;
}
void Point2D::setX(int X){
	this->x=X;
}
void Point2D::setY(int Y){
	this->y=Y;
}
void Point2D::setColor(int Color){
	this->color=Color;
}
void Point2D::setDirection(int d){

	this->direction=d;
}
