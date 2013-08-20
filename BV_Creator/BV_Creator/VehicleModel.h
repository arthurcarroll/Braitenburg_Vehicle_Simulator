#pragma once
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include "Shape.h"
#include "VehicleDrawWindow.h"

#include <string>
#include <stdexcept>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <list>
#include <sys/types.h>
#include <errno.h>

class VehicleModel
{
public:

	VehicleModel(void);
	~VehicleModel(void);
	void save(vector<Shape> shapes , string filename, const char* name);
	void load(VehicleDrawWindow *view , string filename);
	

private:
	xercesc::XercesDOMParser *m_ConfigFileParser;
	xercesc_3_0::DOMDocument* xmlDoc;
	char* m_OptionA;
	char* m_OptionB;
	char* m_OptionC;

	XMLCh* TAG_root;
	XMLCh* TAG_vehicle;
	XMLCh* TAG_sensor;
	XMLCh* TAG_connector;
	XMLCh* TAG_notconnector;
	XMLCh* TAG_Motor;
	XMLCh* id;
	XMLCh* position;
	XMLCh* positionOne;
	XMLCh* positionTwo;
	XMLCh* Motor;
	xercesc::DOMNodeList*   vehicles;
	xercesc::DOMNode* currentVehicle;
	xercesc::DOMElement* currentVehicleElement;
	const XMLCh* vehicleName;

	void loadElementNames();
	void loadSensors(VehicleDrawWindow* view, XMLSize_t xxx);
	void loadConnectors(VehicleDrawWindow* view , XMLSize_t xxx);
	void loadMotors(VehicleDrawWindow* view , XMLSize_t xxx);
};
