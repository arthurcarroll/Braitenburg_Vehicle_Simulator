#include "stdafx.h"
#include "LineSegment.h"


LineSegment::LineSegment(void)
{
}

LineSegment::LineSegment(int X1, int Y1, int X2, int Y2, int NumberOne, int NumberTwo){
	this->pointNumberOne = NumberOne;
	this->pointNumberTwo = NumberTwo;
	this->x1=X1;
	this->x2=X2;
	this->y1=Y1;
	this->y2=Y2;
}

LineSegment::~LineSegment(void)
{
}


void LineSegment::setx1(int X1){
	this->x1=X1;
}
void LineSegment::setx2(int X2){
	this->x2=X2;
}
void LineSegment::sety1(int Y1){
	this->y1=Y1;
}
void LineSegment::sety2(int Y2){
	this->y2=Y2;
}

int LineSegment::getx1(){
	return this->x1;
}
int LineSegment::getx2(){
	return this->x2;
}
int LineSegment::gety1(){
	return this->y1;
}
int LineSegment::gety2(){
	return this->y2;
}