#pragma once
#include "stdafx.h"



enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_FILE_OPEN_BUTTON,
	GUI_ID_CAMERA_RTS,
	GUI_ID_CAMERA_MAYA,
	GUI_ID_MANUAL_TOGGLE
};

struct SAppContext
{
	
	irr::IrrlichtDevice *device;
	irr::video::IVideoDriver* driver;
	irr::scene::ISceneManager* smgr;
	irr::gui::IGUIEnvironment* guienv;
	irr::scene::ICameraSceneNode* camRTS;
	irr::scene::ICameraSceneNode* camFPS;
	bool manualMode;
	
};