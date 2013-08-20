#include "stdafx.h"
#include "Controller.h"

DrawWindow *drawwindow;

void callback( Fl_Widget* o){
	drawwindow->dragging = true;
}

Controller::Controller(void)
{
}


Controller::~Controller(void)
{
}
void Controller::start(){
	Fl_Window *window = new Fl_Window(800, 600);
	Fl_Button *lightSensor = new Fl_Button((window->w())-50, 10, 45, 45, "light");
	Fl_Button *soundSensor = new Fl_Button((window->w())-50, 55, 45, 45, "sound");
	drawwindow = new DrawWindow(*this,0,0,400,400);
	window->add(drawwindow);
	lightSensor->callback(callback);
	soundSensor->callback(callback);
	window->show();
	Fl::run();
}

void Controller::test(){

	//cout << " called it back" << endl;

}