#include "StdAfx.h"
#include "EnvironmentDrawWindow.h"
#include <iostream>
#include <fstream>

EnvironmentDrawWindow::EnvironmentDrawWindow(Controller m,int x,int y,int w,int h,const char *lab):Fl_Widget(x,y,w,h,lab)
{
	MouseX = Fl::event_x();
	MouseY = Fl::event_y();
	xPos = x;
	yPos = y;
	wPos = w;
	hPos = h;
	size =100;
	dragging = false;
	margin = 5;
	this->placing = "";
	this->connecting = false;
	int x1 = xPos+size;
	int y1 = yPos+size;
	int x2 = x1+wPos-(2*size);
	int y2 = y1+hPos-(2*size);
	//this->tooltip("draw Window");
}

EnvironmentDrawWindow::~EnvironmentDrawWindow(void)
{
}

void EnvironmentDrawWindow::draw(void){
	fl_draw_box(FL_FLAT_BOX, xPos, yPos, wPos, hPos, FL_BACKGROUND_COLOR);
	fl_frame("AAAA", xPos, yPos, wPos, hPos);
	fl_draw(this->placing.c_str(),xPos+2,yPos+(GRIDSPACING/2)+2);
	this->drawGrid();
	
	for(int i=0; i < shapes.size(); i++)
	{
		Shape s = shapes.at(i);
		Point2D p = s.location;
		//fl_draw(s.name.c_str(),p.getX(),p.getY());
		if(s.name == names::sCircle){
			fl_pie(p.getX(), p.getY(), GRIDSPACING, GRIDSPACING, 0, 360);
		}
		if(s.name == names::sBox){
			fl_draw_box(FL_FLAT_BOX, p.getX(),p.getY(),GRIDSPACING, GRIDSPACING,FL_BLACK);
		}
		if(s.name == names::sLight){
			fl_circle(p.getX()+(GRIDSPACING/2),p.getY()+(GRIDSPACING/2),GRIDSPACING/2);
			fl_draw("LS",p.getX()-8+(GRIDSPACING/2),p.getY()+5+(GRIDSPACING/2));
		}
		if(s.name == names::sSound){
			fl_circle(p.getX()+(GRIDSPACING/2),p.getY()+(GRIDSPACING/2),GRIDSPACING/2);
			fl_draw("SS",p.getX()-8+(GRIDSPACING/2),p.getY()+5+(GRIDSPACING/2));
		}
		if(s.name == names::sVehicles){
			fl_draw_box(FL_FLAT_BOX, p.getX()+(GRIDSPACING/4),p.getY()+(GRIDSPACING/4),GRIDSPACING-(GRIDSPACING/2),GRIDSPACING-(GRIDSPACING/2),FL_BLACK);
		}
	}

	
}

int EnvironmentDrawWindow::handle(int event){
	if(event==FL_PUSH){
		if(connecting == true){
			int xNorm = normalizeX(Fl::event_x());
			int yNorm = normalizeY(Fl::event_y());
			if(xNorm != -1 && yNorm != -1){
				if(this->placing == names::sVehicles){
					shapes.push_back(Shape(Point2D(xNorm,yNorm, 0 , 5 , 1),this->placing, this->nextFileName));
				}
				else{
					shapes.push_back(Shape(Point2D(xNorm,yNorm, 0 , 5 , 1),this->placing , ""));
				}
				this->redraw();
			}
		}
	}
	return 1;
}

void EnvironmentDrawWindow::drawGrid(){
	for(int i=this->xPos+GRIDSPACING; i< this->wPos+xPos; i+=GRIDSPACING){
		
		fl_line(i, yPos+GRIDSPACING, i, this->hPos+yPos-GRIDSPACING); 
	}
	for(int i=this->yPos+GRIDSPACING; i< this->hPos+yPos; i+=GRIDSPACING){
		
		fl_line(xPos+GRIDSPACING, i, xPos+wPos-GRIDSPACING, i); 
	}
}

int EnvironmentDrawWindow::normalizeX(int x){
	bool first = true;
	for(int i=this->xPos+GRIDSPACING; i< this->wPos+xPos; i+=GRIDSPACING){
		if(i > x){
			if(first){
				return -1;
			}
			return (i-GRIDSPACING);
		}
		first = false;
	}
	return -1;
}

int EnvironmentDrawWindow::normalizeY(int y){
	bool first = true;
	for(int i=this->yPos+GRIDSPACING; i< this->hPos+yPos; i+=GRIDSPACING){
		if(i > y){
			if(first){
				return -1;
			}
			return (i-GRIDSPACING);
		}
		first = false;
	}
	return -1;
}


