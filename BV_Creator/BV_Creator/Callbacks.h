// Callbacks have to be static functions so the purpose of 
// this file is really just to move to code out of controller for
// readability
#pragma once
#include "FileChooser.h"
#include "VehicleDrawWindow.h"
#include "EnvironmentDrawWindow.h"
#include "VehicleModel.h"
#include "EnvironmentModel.h"
#include <FL/fl_ask.H>
#include <string>

using namespace std;

VehicleDrawWindow *vehDrawWindow;
EnvironmentDrawWindow *envDrawWindow;
VehicleModel *vehModel;
EnvironmentModel *envModel;
Fl_Group *vehicleTab;
Fl_Group *envTab;
string currentView = names::sVehicles;
Fl_Tabs *tabs; 
FileChooser* fileChooser;

void shape_cb( Fl_Widget* o){
	vehDrawWindow->placing = o->label();
	vehDrawWindow->dragging = true;
	vehDrawWindow->connecting=false;
	//vehDrawWindow->currentShape = o->label();
	fl_cursor(FL_CURSOR_CROSS);
	vehDrawWindow->redraw();
	vehicleTab->redraw();
	tabs->redraw();
}

void open_cb(Fl_Widget* o, void*) {
	vehDrawWindow->file = fileChooser->chooseFile(Fl_File_Chooser::SINGLE, "*.xml" , "Open File");
}

void connector_cb(Fl_Widget* o)
{
	fl_cursor(FL_CURSOR_CROSS);
	vehDrawWindow->placing = o->label();
	vehDrawWindow->connecting = true;
	vehDrawWindow->notConnector = false;
	vehDrawWindow->dragging=false;
	vehDrawWindow->redraw();
}

void notConnector_cb(Fl_Widget* o)
{
	fl_cursor(FL_CURSOR_CROSS);
	vehDrawWindow->placing = o->label();
	vehDrawWindow->connecting = true;
	vehDrawWindow->notConnector=true;
	vehDrawWindow->redraw();
}
// Callback: when user picks 'Quit'
void quit_cb(Fl_Widget*, void*) {
	exit(0);
}

void box_cb(Fl_Widget* o, void*){
	fl_cursor(FL_CURSOR_CROSS);
	envDrawWindow->placing = o->label();
	envDrawWindow->connecting = true;
	envDrawWindow->redraw();
}

void circle_cb(Fl_Widget* o, void*){
	fl_cursor(FL_CURSOR_CROSS);
	envDrawWindow->placing = o->label();
	envDrawWindow->connecting = true;
	envDrawWindow->redraw();
}

void lightStim_cb(Fl_Widget* o, void*){
	fl_cursor(FL_CURSOR_CROSS);
	envDrawWindow->placing = o->label();
	envDrawWindow->connecting = true;
	envDrawWindow->redraw();
}

void soundStim_cb(Fl_Widget* o, void*){
	fl_cursor(FL_CURSOR_CROSS);
	envDrawWindow->placing = o->label();
	envDrawWindow->connecting = true;
	envDrawWindow->redraw();
}

void addVehicle_cb(Fl_Widget* o, void*){
	string filename = fileChooser->chooseFile(Fl_File_Chooser::CREATE, "*.veh", "Select A Vehicle");
	if(filename != ""){
		envDrawWindow->placing = o->label();
		envDrawWindow->nextFileName = filename;
		envDrawWindow->connecting = true;
		fl_cursor(FL_CURSOR_CROSS);
		envDrawWindow->redraw();
	}
}

void openMap_cb(Fl_Widget* o, void*){
	string filename = fileChooser->chooseFile(Fl_File_Chooser::CREATE, "*.map", "Open Map");
	envModel->load(envDrawWindow ,filename);
}

void saveMap_cb(Fl_Widget* o, void*){
	string filename = fileChooser->chooseFile(Fl_File_Chooser::CREATE, "*.map", "Save Map As");
	envModel->save( envDrawWindow->shapes, filename);
	
	
}

void loadVeh_cb(Fl_Widget* o, void*){
	string filename = fileChooser->chooseFile(Fl_File_Chooser::CREATE, "*.veh", "Open Vehicle");
	vehModel->load(vehDrawWindow ,filename);
}

void saveVeh_cb(Fl_Widget* o, void*){
	const char* name = fl_input("Choose Vehicle Name", "New Vehicle");
	string filename = fileChooser->chooseFile(Fl_File_Chooser::CREATE, "*.veh", "Save Vehicle As");
	vehModel->save(vehDrawWindow->shapes, filename, name);
}


void clearVeh_cb(Fl_Widget* o, void*){
	vehDrawWindow->shapes.clear();
	vehDrawWindow->redraw();
}

void clearEnv_cb(Fl_Widget* o, void*){
	envDrawWindow->shapes.clear();
	fl_cursor(FL_CURSOR_ARROW);
	envDrawWindow->redraw();
}
