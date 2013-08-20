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
#include "EnvironmentDrawWindow.h"

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

class EnvironmentModel
{
public:
	EnvironmentModel(void);
	~EnvironmentModel(void);
	void save(std::vector<Shape> shapes , std::string filename);
	void load(EnvironmentDrawWindow *view , string configFile );
private:
	xercesc::XercesDOMParser *m_ConfigFileParser;
	xercesc_3_0::DOMDocument* xmlDoc;

	char* m_OptionA;
	char* m_OptionB;
	char* m_OptionC;

	//General Attributes
	XMLCh* id;
	XMLCh* TAG_root;
	XMLCh* positionX;
	XMLCh* positionY;
	

	// Vehicle Attributes
	XMLCh* TAG_vehicle;
	

	// Obstacle Attributes
	XMLCh* TAG_obstacle;
	
	// Stimuli Attributes
	XMLCh* TAG_stimuli;

	

	xercesc::DOMNodeList*   elements;
	xercesc::DOMNode* currentNode;
	xercesc::DOMElement* currentElement;

	
	
	const XMLCh* vehicleName;


	void loadElementNames();

	void loadObjects(EnvironmentDrawWindow *view , XMLCh* type);
	void loadVehicles(EnvironmentDrawWindow *view);
};
