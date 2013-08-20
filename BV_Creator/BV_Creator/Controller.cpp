#include "stdafx.h"
#include "Controller.h"




// callbacks for all widgets are in this header
#include "Callbacks.h"

Controller::Controller(void)
{

}

Controller::~Controller(void)
{
}

void Controller::start(){
	
	int width = 800;
	int height = 600;
	int buttonWidth = 110;
	int buttonHeight = 50;
	int buttonSpacing = 10;

	Fl_Window *window = new Fl_Window(width, height);
	{
	int tabWidth = width - 60;
	int tabHeight = height - 60;
	int tabstartX = 10;
	int tabstartY = 20;
	tabs = new Fl_Tabs(tabstartX,tabstartY,tabWidth,tabHeight);
	{

		int groupsx = tabstartX+30;
		int groupsy = tabstartY+30;
		
		vehicleTab = new Fl_Group(groupsx,groupsy,tabWidth,tabHeight,"Vehicles");
		{
			int buttonPositionX = tabWidth - buttonWidth;
			int buttonPositionY = buttonSpacing + groupsy;
			Fl_Button *lightSensor = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sLight);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *soundSensor = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sSound);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *Sensor = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sSensor);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *actuator = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sMotor);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *connector = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sConnector);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *notConnector = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sNotConnecotor);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *clearVeh = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sClear);
			vehDrawWindow = new VehicleDrawWindow(*this,groupsx+30,groupsy+30,400,400);
			clearVeh->callback(clearVeh_cb);
			lightSensor->callback(shape_cb);
			soundSensor->callback(shape_cb);
			actuator->callback(shape_cb);
			connector->callback(connector_cb);
			notConnector->callback(notConnector_cb);

		}
		vehicleTab->end();
	
		envTab = new Fl_Group(groupsx,groupsy,tabWidth,tabHeight,"Environments");
		{
			int buttonPositionX = tabWidth - buttonWidth;
			int buttonPositionY = buttonSpacing + groupsy;
			Fl_Button *box = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sBox);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *circle = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sCircle);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *vehicleButton = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sVehicles);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *lightStim = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sLight);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *soundStim = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sSound);
			buttonPositionY += buttonHeight + buttonSpacing;
			Fl_Button *clearEnv = new Fl_Button(buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, names::sClear);
			envDrawWindow = new EnvironmentDrawWindow(*this,groupsx+30,groupsy+30,400,400);
			clearEnv->callback(clearEnv_cb);
			box->callback(box_cb);
			circle->callback(circle_cb);
			vehicleButton->callback(addVehicle_cb);
			lightStim->callback(lightStim_cb);
			soundStim->callback(soundStim_cb);

		}
		envTab->end();
		
		
	}
	tabs->end();
	
	//tabs->align(FL_ALIGN_LEFT_TOP);
	}
	Fl_Menu_Bar menubar(0,0,230,20);
	menubar.add("File/Open Map", 0, openMap_cb);
	menubar.add("File/Save Map", 0, saveMap_cb);
	menubar.add("File/Open Vehicle", 0, loadVeh_cb);
	menubar.add("File/Save Vehicle", 0, saveVeh_cb);
	menubar.add("File/Quit", 0, quit_cb);
	menubar.add("Edit/TODO", 0, quit_cb);
	menubar.add("Tools/TODO", 0, quit_cb);
	menubar.add("Help/TODO", 0, quit_cb);
	window->end();
	window->show();
	vehModel = new VehicleModel();
	envModel = new EnvironmentModel();
	Fl::run();
}







