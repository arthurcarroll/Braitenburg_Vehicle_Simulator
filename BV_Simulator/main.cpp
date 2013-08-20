#include "stdafx.h"
#include "GroundPlane.h"
#include "Stimuli.h"
#include "Box.h"
#include "Vehicle.h"
#include "EventReciever.h"
#include "guicon.h"
#include <vector>
#include <math.h>

using namespace std;
using namespace irr;
using namespace core;

SAppContext *context;
EventReceiver *receiver;


void setupGraphics();
void setupCamera();
void setupGUI();
void setupScene();
void move(irr::scene::ISceneNode *node, irr::core::vector3df vel);
irr::core::vector3df faceTarget(irr::core::vector3df targetpos, irr::core::vector3df nodepos);
void manualMove();

std::vector<BV_Object> gameObjects;
std::vector<Stimuli> stims;

float xRotation=0;
float yRotation=0;

float camX = 0;
float camY = 200;
float camZ = 0;

u32 prevTime;
Vehicle* veh;
Vehicle* veh2;
irr::gui::IGUIElement *modeText;

int main()
{			
	context = new SAppContext();
	context->manualMode = true;
	RedirectIOToConsole();
	cout << "creating graphics" << endl;
	setupGraphics();
	cout << "creating window" << endl;
	setupCamera();
	setupGUI();
	setupScene();
	receiver = new EventReceiver(context);
	context->device->setEventReceiver(receiver);
	


	veh = new Vehicle(context->smgr,0,0,0);
	//veh2 = new Vehicle(context->smgr,-50,0,30);
	float timeStep = 1.0f / 60.0f;
	int iterations = 10;
	int Bcount = 0;
	prevTime = context->device->getTimer()->getTime();
	int mDeBounce = 0;
	

	while(context->device->run())
	{
		if(receiver->IsKeyDown(irr::KEY_KEY_Q)){
			break;
		}

		if(receiver->IsKeyDown(irr::KEY_KEY_F)){
			
		}

		if(receiver->IsKeyDown(irr::KEY_KEY_R)){
			
		}

		if(receiver->IsKeyDown(irr::KEY_UP)){
			core::vector3df oldPos = context->camRTS->getPosition();
			core::vector3df oldTar = context->camRTS->getTarget();
			oldPos.X = oldPos.X + 1;
			oldTar.X = oldTar.X + 1;
			context->camRTS->setPosition(oldPos);
			context->camRTS->setTarget(oldTar);
		}
		if(receiver->IsKeyDown(irr::KEY_DOWN)){
			core::vector3df oldPos = context->camRTS->getPosition();
			core::vector3df oldTar = context->camRTS->getTarget();
			oldPos.X = oldPos.X - 1;
			oldTar.X = oldTar.X - 1;
			context->camRTS->setPosition(oldPos);
			context->camRTS->setTarget(oldTar);
		}

		if(receiver->IsKeyDown(irr::KEY_RIGHT)){
			core::vector3df oldPos = context->camRTS->getPosition();
			core::vector3df oldTar = context->camRTS->getTarget();
			oldPos.Z = oldPos.Z - 1;
			oldTar.Z = oldTar.Z - 1;
			context->camRTS->setPosition(oldPos);
			context->camRTS->setTarget(oldTar);
		}
		if(receiver->IsKeyDown(irr::KEY_LEFT)){
			core::vector3df oldPos = context->camRTS->getPosition();
			core::vector3df oldTar = context->camRTS->getTarget();
			oldPos.Z = oldPos.Z + 1;
			oldTar.Z = oldTar.Z + 1;
			context->camRTS->setPosition(oldPos);
			context->camRTS->setTarget(oldTar);
		}

		if(receiver->IsKeyDown(irr::KEY_PLUS)){
			core::vector3df oldPos = context->camRTS->getPosition();
			core::vector3df oldTar = context->camRTS->getTarget();
			oldPos.Y = oldPos.Y - 1;
			oldTar.Y = oldTar.Y - 1;
			context->camRTS->setPosition(oldPos);
			context->camRTS->setTarget(oldTar);
		}
		if(receiver->IsKeyDown(irr::KEY_MINUS)){
			core::vector3df oldPos = context->camRTS->getPosition();
			core::vector3df oldTar = context->camRTS->getTarget();
			oldPos.Y = oldPos.Y + 1;
			oldTar.Y = oldTar.Y + 1;
			context->camRTS->setPosition(oldPos);
			context->camRTS->setTarget(oldTar);
		}


		if(context->manualMode){
			manualMove();
		}else{
			veh->update(context->device->getTimer()->getTime(), stims);
			//veh2->update(context->device->getTimer()->getTime(), stims);
		}
		context->driver->beginScene(true, true, video::SColor(255,100,101,140));
		context->smgr->drawAll();
		context->guienv->drawAll();
		context->driver->endScene();
		prevTime = context->device->getTimer()->getTime();
	}
	context->device->drop();
	return 0;
}

void setupGraphics(){
	context->device =createDevice( video::EDT_DIRECT3D9 , dimension2d<u32>(900, 700), 16, false, false, false, receiver);
	context->driver = context->device->getVideoDriver();
	context->smgr = context->device->getSceneManager();
	context->device->setWindowCaption(L"Braitenburg Simulator");
	
	if (!context->device){
		exit(1);
	}
	

}

void setupCamera(){
	scene::ILightSceneNode* light = context->smgr->addLightSceneNode(0, vector3df(400, 300, -400), video::SColorf(1.0f, 1.0f, 1.0f), 9000.0f, -1);
	context->camFPS = context->smgr->addCameraSceneNodeMaya(0,500.0,200.0,500.0,-1);
	context->camRTS = context->smgr->addCameraSceneNode(0,core::vector3df(0,500,0),core::vector3df(0,0,0),-1);
}

void setupGUI(){
	context->guienv = context->device->getGUIEnvironment();
	int yPos = 100;
	context->guienv->addButton(rect<s32>(10,yPos,110,yPos + 32), 0, GUI_ID_QUIT_BUTTON, L"Quit", L"Exits Program");
	yPos+=40;
	context->guienv->addButton(rect<s32>(10,yPos,110,yPos + 32), 0, GUI_ID_FILE_OPEN_BUTTON, L"File Open", L"Opens a file");
	yPos+=40;
	context->guienv->addButton(rect<s32>(10,yPos,110,yPos + 32), 0, GUI_ID_MANUAL_TOGGLE, L"Manual", L"Toggle Manual Mode");
	yPos+=40;
	context->guienv->addButton(rect<s32>(10,yPos,110,yPos + 32), 0, GUI_ID_CAMERA_RTS, L"Camera RTS", L"RTS Camera");
	yPos+=40;
	context->guienv->addButton(rect<s32>(10,yPos,110,yPos + 32), 0, GUI_ID_CAMERA_MAYA, L"Camera Maya", L"Maya Camera");
	modeText = context->guienv->addStaticText( L"manual", core::rect<s32>(10, 10, 200, 100));
}

void setupScene(){
	
	GroundPlane ground1(context->smgr, 0,0,200,1);
	GroundPlane ground2(context->smgr, -200,0,200,1);
	GroundPlane ground3(context->smgr, -200,0,0,1);
	GroundPlane ground(context->smgr, 0,0,0,1);

	stims.push_back(Stimuli(context->smgr, 30,10,-45,"light",41));
	stims.push_back(Stimuli(context->smgr, 110,10,-50,"light",42));
	stims.push_back(Stimuli(context->smgr, 180,10,-16,"light", 30));

	stims.push_back(Stimuli(context->smgr, -30,10,45,"light", 41));
	stims.push_back(Stimuli(context->smgr, -110,10,50,"light", 42));
	stims.push_back(Stimuli(context->smgr, -180,10,16,"light", 30));
	
	//Box box(context->smgr, 30,0,-30);
}

//--- move acording to rotation --- 
void move(irr::scene::ISceneNode *node, //node to move 
		  irr::core::vector3df vel) //velocity vector 
{ 
	irr::core::matrix4 m; 
	m.setRotationDegrees(node->getRotation()); 
	m.transformVect(vel); 
	node->setPosition(node->getPosition() + vel); 
	node->updateAbsolutePosition(); 
} 

void manualMove(){

	if(receiver->IsKeyDown(irr::KEY_KEY_W)){
		move(veh->node,core::vector3df(0,0,-0.75f));
		veh->node->setRotation(core::vector3df(xRotation,yRotation--,0));
		move(veh->node,core::vector3df(0,0,-0.05f));
		veh->node->setRotation(core::vector3df(xRotation,yRotation++,0));
	}
	if(receiver->IsKeyDown(irr::KEY_KEY_A)){
		//move(veh->node,core::vector3df(0,0,-0.05f));
		veh->node->setRotation(core::vector3df(xRotation,yRotation--,0));
	}
	if(receiver->IsKeyDown(irr::KEY_KEY_D)){
		//move(veh->node,core::vector3df(0,0,-0.05f));
		veh->node->setRotation(core::vector3df(xRotation,yRotation++,0));
	}
	if(receiver->IsKeyDown(irr::KEY_KEY_T)){
		yRotation++;
		for(int k=0; k< veh->motors.size(); k++){

			veh->motors.at(k)->node->setRotation(core::vector3df(yRotation,0,0));
		}
	}
	if(receiver->IsKeyDown(irr::KEY_KEY_R)){
		 veh->node->setRotation(core::vector3df(xRotation++,yRotation,0));
	}
	if(receiver->IsKeyDown(irr::KEY_KEY_E)){
		 veh->node->setRotation(core::vector3df(xRotation--,yRotation,0));
	}
}