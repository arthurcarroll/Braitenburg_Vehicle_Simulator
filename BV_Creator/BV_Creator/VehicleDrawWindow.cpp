#include "stdafx.h"
#include "VehicleDrawWindow.h"
#include <iostream>
#include "Shape.h"
#include "GlobalNames.h"



using namespace std;



Controller controller;
VehicleDrawWindow::VehicleDrawWindow(Controller m,int x,int y,int w,int h,const char *lab):Fl_Widget(x,y,w,h,lab)
{
	this->placing = "";
	pointNumber = 0;
	controller = m;
	radius=5;
	file = "NONE";
	MouseX = Fl::event_x();
	MouseY = Fl::event_y();
	xPos = x;
	yPos = y;
	wPos = w;
	hPos = h;
	size =100;
	dragging = false;
	connecting = false;
	firstPoint = false;
	margin = 5;
	numPoints = 8;
	int x1 = xPos+size;
	int y1 = yPos+size;
	int x2 = x1+wPos-(2*size);
	int y2 = y1+hPos-(2*size);
	int vertSpacing = (y2-y1)/(numPoints-1);
	// left vert circles
	this->addVertPoints(x1,y1, vertSpacing,1);
	// right vert circles
	this->addVertPoints(x2,y1, vertSpacing,3);
	// top horiz circles
	this->addHorizPoints(x1+vertSpacing,y1,vertSpacing,2);
	// top horiz circles
	this->addHorizPoints(x1+vertSpacing,y2,vertSpacing,4);
}//VehicleDrawWindow

VehicleDrawWindow::~VehicleDrawWindow(void)
{
}

int VehicleDrawWindow::handle(int event)
{
	if(event==FL_PUSH){
		int pn = checkPoint(Fl::event_x(),Fl::event_y());
		if(pn == -1){
			this->placing = "";
			return 1;
		}
	}
	// placing a connector
	if(connecting == true){
		// mouse pressed
		if(event==FL_PUSH){
			// first point already set
			if(firstPoint == true){
				vector<LineSegment> newShape;
				int pn = checkPoint(Fl::event_x(),Fl::event_y());
				if(pn != -1){
					newShape.push_back(LineSegment(snapPoints.at(pn).getX(),snapPoints.at(pn).getY(),prevPoint.getX(),prevPoint.getY(), snapPoints.at(pn).pointNumber, prevPoint.pointNumber));
					if(notConnector == true){
						this->shapes.push_back(Shape(newShape,Point2D(0,0,FL_RED,1,0),names::sNotConnecotor)); 
						//fl_cursor(FL_CURSOR_ARROW);
					}else{
						this->shapes.push_back(Shape(newShape,Point2D(0,0,FL_GREEN,1,0),names::sConnector));
						//fl_cursor(FL_CURSOR_ARROW);
					}
					this->placing = prevPlacing;
					firstPoint = false;
					//connecting = false;
					notConnector = false;
					this->redraw();
				}

			}else{ // create first point
				int pn = checkPoint(Fl::event_x(),Fl::event_y());
				if(pn != -1){
					prevPoint.setX(snapPoints.at(pn).getX());
					prevPoint.setY(snapPoints.at(pn).getY());
					prevPoint.pointNumber = snapPoints.at(pn).pointNumber;
					firstPoint = true;
					prevPlacing = this->placing;
					this->placing = "Choose Second Point";
					this->redraw();
				}
			}
		}
	}
	// not placing a connector
	if(connecting == false){
		// mouse pressed
		if(event==FL_PUSH){
			// waiting for shape to be added
			if(dragging){
				int point = checkPoint(Fl::event_x(),Fl::event_y());
				// add shape if a snap point was clicked
				if(point!=-1){
					this->addShape(snapPoints.at(point));
					//dragging = false;
					this->redraw();
				}
			}else{
				int point = checkPoint(Fl::event_x(),Fl::event_y());
				if(point!=-1){
					this->resetPoints(snapPoints);
					snapPoints.at(point).setColor(FL_RED);
					this->redraw();
				}else{
					this->resetPoints(snapPoints);
					this->redraw();
				}
				//dragging = false;
			}
			//dragging = false;
			//fl_cursor(FL_CURSOR_ARROW);
			this->redraw();
		}

	}
	return 1;
}//handle

void VehicleDrawWindow::draw(void)
{

	// background box
	fl_draw_box(FL_FLAT_BOX, xPos, yPos, wPos, hPos, FL_BACKGROUND_COLOR);
	// border around box
	fl_frame("AAAA", xPos, yPos, wPos, hPos);
	fl_frame("AAAA", xPos+size, yPos+size, wPos-(2*size), hPos-(2*size));
	this->drawPoints(snapPoints);
	//vector<Shape> shapes = this->getShapes();
	fl_draw(this->placing.c_str(), xPos+50, yPos+50);
	for(int i=0; i < shapes.size(); i++)
	{
		Shape s = shapes.at(i);
		Point2D point = s.location;
		vector<LineSegment> lines = s.getShape();

		for(int y=0; y < lines.size(); y++){
			LineSegment line = lines.at(y);


			if(s.name == names::sConnector || s.name== names::sNotConnecotor){
				if(s.name == names::sConnector){
				//fl_color(s.location.color);
					fl_color(FL_BLUE);
				}else{
					fl_color(FL_RED);
				}
				fl_line(line.getx1(), line.gety1(), line.getx2(), line.gety2());
			}else{
				fl_color(FL_BLACK);
				// top
				if(point.direction == 2){
					fl_line(point.getX()-line.getx1(), point.getY()-line.gety1(), point.getX()-line.getx2(), point.getY()-line.gety2());
				}
				// left
				if(point.direction == 1){
					fl_line(point.getX()-line.gety1(), point.getY()-line.getx1(), point.getX()-line.gety2(), point.getY()-line.getx2());
				}
				// right
				if(point.direction == 3){
					//fl_draw(s.name.c_str(), point.getX()+8, point.getY()+5);
					fl_line(point.getX()+line.gety1(), point.getY()+line.getx1(), point.getX()+line.gety2(), point.getY()+line.getx2());
				}
				// bottom
				if(point.direction == 4){
					//fl_draw(s.name.c_str(), point.getX()-5, point.getY()+16);
					fl_line(point.getX()+line.getx1(), point.getY()+line.gety1(), point.getX()+line.getx2(), point.getY()+line.gety2());
				}
			}
		}
	}
}//draw

void VehicleDrawWindow::addVertPoints(int xStart, int yStart, int yTick, int side)
{
	for(int i=0; i < numPoints; i++){
		snapPoints.push_back(Point2D(xStart,yStart,FL_BLACK,side, pointNumber++));
		yStart+=yTick;
	}
}//drawVertPoints

void VehicleDrawWindow::addHorizPoints(int xStart, int yStart, int xTick, int side)
{
	for(int i=0; i < (numPoints-2); i++){
		snapPoints.push_back(Point2D(xStart,yStart,FL_BLACK,side, pointNumber++));
		xStart+=xTick;
	}
}// drawHorizPoints

void VehicleDrawWindow::drawPoints(vector<Point2D> points)
{
	for (int i = 0; i < points.size(); i++){
		Point2D nextPoint = points.at(i);
		fl_color(nextPoint.getColor());
		fl_circle(nextPoint.getX(),nextPoint.getY(),radius);
	}
}

int VehicleDrawWindow::checkPoint(int pointX, int pointY)
{
	for (int i = 0; i < snapPoints.size(); i++){
		Point2D nextPoint = snapPoints.at(i);
		if(inMargin(nextPoint.getX(),pointX,margin) && inMargin(nextPoint.getY(),pointY,margin))
		{
			return i;
		}
	}
	return -1;
}

bool VehicleDrawWindow::inMargin(int point1, int point2, int pointMargin)
{
	int diff = abs(point1-point2);
	if(diff < pointMargin)
	{
		return true;
	}else{
		return false;
	}
}

void VehicleDrawWindow::resetPoints(vector<Point2D> &points)
{
	for (int i = 0; i < points.size(); i++){
		points.at(i).setColor(FL_BLACK);

	}
}



void VehicleDrawWindow::addShape(Point2D p){

	if(placing == names::sLight){
		vector<LineSegment> light;
		light.push_back(LineSegment(0,0,0,8,0,0));
		light.push_back(LineSegment(0,8,-8,16,0,0));
		light.push_back(LineSegment(0,8,8,16,0,0));
		shapes.push_back(Shape(light,p,placing));

	}
	if(placing == names::sSound){
		vector<LineSegment> light;
		light.push_back(LineSegment(0,0,0,8,0,0));
		light.push_back(LineSegment(-4,8,0,8,0,0));
		light.push_back(LineSegment(-4,8,-4,16,0,0));
		light.push_back(LineSegment(4,8,0,8,0,0));
		light.push_back(LineSegment(4,8,4,16,0,0));
		shapes.push_back(Shape(light,p,placing));

	}
	if(placing == names::sMotor){
		vector<LineSegment> light;
		light.push_back(LineSegment(-8,0,-8,16,0,0));
		light.push_back(LineSegment(8,0,8,16,0,0));
		light.push_back(LineSegment(-8,16,8,16,0,0));
		shapes.push_back(Shape(light,p,placing));

	}
	this->redraw();
}


