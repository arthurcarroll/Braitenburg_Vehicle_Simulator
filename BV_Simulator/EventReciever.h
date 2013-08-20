#pragma once
#include "SAppContext.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EventReceiver : public IEventReceiver
{


public:
	SAppContext* Context;
	EventReceiver(SAppContext * context) 
	{
		this->Context = context;
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}


	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{

		if (event.EventType == EET_MOUSE_INPUT_EVENT && event.MouseInput.Event == EMIE_MOUSE_WHEEL)
		{
			//this->Context->camera->Update(Context->cam,Context->device,Context->driver);
		} 

		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			//irr::gui::IGUIEnvironment* env = Context->guienv;

			switch(event.GUIEvent.EventType)
			{	  

			case EGET_FILE_SELECTED:
				{
					// load the model file, selected in the file open dialog
					IGUIFileOpenDialog* dialog = (IGUIFileOpenDialog*)event.GUIEvent.Caller;
					std::cout << "File: " << core::stringc(dialog->getFileName()).c_str() << std::endl;
					//Context->camRTS->setPosition(core::vector3df(0,200,0));
					//Context->camRTS->setTarget(core::vector3df(0,0,0));
					//loadModel(core::stringc(dialog->getFileName()).c_str());

					
				}
				break;

			case EGET_SCROLL_BAR_CHANGED:

				break;
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case GUI_ID_QUIT_BUTTON:
					Context->device->closeDevice();
					break;

				case GUI_ID_MANUAL_TOGGLE:
					Context->manualMode = !Context->manualMode;
					break;

				case GUI_ID_FILE_OPEN_BUTTON:
					std::cout << "Open" << std::endl;
					Context->guienv->addFileOpenDialog(L"Please select a model file to open");
					//Context->camRTS->setPosition(core::vector3df(100,0,0));
					//Context->camRTS->setTarget(core::vector3df(100,0,0));

					std::cout << "passed" << std::endl;
					break;
				case  GUI_ID_CAMERA_MAYA:
					std::cout << "maya cam" << std::endl;
					Context->camFPS->setPosition(core::vector3df(0,100,20));
					Context->smgr->setActiveCamera(Context->camFPS);
					break;
				case  GUI_ID_CAMERA_RTS:
					Context->camRTS->setPosition(core::vector3df(0,100,0));
					Context->camRTS->setTarget(core::vector3df(0,0,0));
					Context->smgr->setActiveCamera(Context->camRTS);
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}




		}
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT){
			//cout << "recieved Key" << endl;
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;


		}

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}



private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

};