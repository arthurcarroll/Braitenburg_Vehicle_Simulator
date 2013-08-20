#include "StdAfx.h"
#include "VehicleModel.h"
#include "GlobalNames.h"


using namespace std;
using namespace xercesc;


/*!
 1. parses a vehicle XML file and loads all shapes in the vehicle creator
	using xerces XML library
 2. writes a vehicle to state to a file, using text formatting
*/
VehicleModel::VehicleModel(void)
{
	try
	{
		XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
	}
	catch( XMLException& e )
	{
		char* message = XMLString::transcode( e.getMessage() );
		cerr << "XML toolkit initialization error: " << message << endl;
		XMLString::release( &message );
		// throw exception here to return ERROR_XERCES_INIT
	}
	m_ConfigFileParser = new XercesDOMParser;
	m_ConfigFileParser->setValidationSchemaFullChecking(true);
	

	this->loadElementNames();
}

VehicleModel::~VehicleModel(void)
{
}
/*!
 save current vehicle to a file
 shapes= vector holding shapes to save, must be <Shape> type
 filename = name of the file to write to
 name = the name of this vehicle
*/
void VehicleModel::save(vector<Shape> shapes, string filename, const char* name){
	ofstream myfile;
	if(filename.length() == 0 || name == NULL){
		return;
	}
	myfile.open (filename.c_str());
	myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	myfile << "<" << names::sRoot << ">" << endl;
	myfile << "<" << names::sVehicles << " " <<names::sID << "=\"" << name << "\">" << endl;
	for(int i=0; i < shapes.size(); i++){

		Shape s = shapes.at(i);
		if(s.name == names::sConnector || s.name == names::sNotConnecotor){
			vector<LineSegment> line = s.getShape();
			LineSegment l = line.at(0);
			myfile << "		<"<< names::sConnector << " " << " " <<names::sID << "=\"" << s.name << "\" " << names::sPositionOne<< "=\"" << 
				l.pointNumberOne <<"\" "<< names::sPositionTwo << "=\"" << l.pointNumberTwo <<"\" " ">" << endl;
			myfile << "		</" << names::sConnector << ">" << endl;
		}
		else if(s.name == names::sMotor){
			myfile << "		<" << names::sMotor << " " << names::sPosition << "=\"" << s.location.pointNumber << "\" "<< ">" << endl;
			myfile << "		</" << names::sMotor <<">" << endl;
		}else{
			myfile << "		<" << names::sSensor << " " << names::sID << "=\"" << s.name << "\" " << names::sPosition <<"=\"" << s.location.pointNumber <<"\" "<< ">" << endl;
			myfile << "		</"<< names::sSensor << ">" << endl;
		}
	}
	myfile << "</" << names::sVehicles << ">" << endl;
	myfile << "</" << names::sRoot << ">" << endl;
	myfile.close();
}

void VehicleModel::load(VehicleDrawWindow *view, string configFile){
	// Test to see if the file is ok.

	struct stat fileStatus;

	int iretStat = stat(configFile.c_str(), &fileStatus);
	if( iretStat == ENOENT )
		throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
	else if( iretStat == ENOTDIR )
		throw ( std::runtime_error("A component of the path is not a directory."));
	else if( iretStat == EACCES )
		throw ( std::runtime_error("Permission denied."));
	else if( iretStat == ENAMETOOLONG )
		throw ( std::runtime_error("File can not be read\n"));

	// Configure DOM parser.

	m_ConfigFileParser->setValidationScheme( XercesDOMParser::Val_Never );
	m_ConfigFileParser->setDoNamespaces( false );
	m_ConfigFileParser->setDoSchema( false );
	m_ConfigFileParser->setLoadExternalDTD( false );
	try
	{
		if(configFile == "")return;
		m_ConfigFileParser->parse( configFile.c_str() );

		// no need to free this pointer - owned by the parent parser object
		xmlDoc = m_ConfigFileParser->getDocument();


		view->shapes.clear();

		// using XMLUtils.h as a dirty way to break up some of this code
		// will refactor later

		
	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		ostringstream errBuf;
		errBuf << "Error parsing file: " << message << flush;
		XMLString::release( &message );
	}


	/******************************************************************
	 ******************************************************************
		ACTUAL PARSING STARTS
     ******************************************************************
	 ******************************************************************
	 */
	// Get the top-level element: Name is "root". No attributes for "root"
	DOMElement* elementRoot = xmlDoc->getDocumentElement();
	// if doc is empty throw an error
	if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));
	cout << XMLString::transcode(TAG_vehicle);
	vehicles = elementRoot->getElementsByTagName(TAG_vehicle);
	const  XMLSize_t vehicleNodeCount = vehicles->getLength();
	cout << "num vehicles: " << vehicles->getLength() << endl;
	for( XMLSize_t xxx = 0; xxx < vehicleNodeCount; ++xxx )
	{
		// Open each Vehicle
		currentVehicle = vehicles->item(xxx);
		currentVehicleElement = dynamic_cast< xercesc::DOMElement* >( currentVehicle );
		vehicleName  = currentVehicleElement->getAttribute(id);
		m_OptionA = XMLString::transcode(vehicleName);
		//cout << "vehicle one name: " << m_OptionA << endl;
		loadSensors(view , xxx);
		loadConnectors(view, xxx);
		loadMotors(view , xxx);
	}

	view->redraw();
}





void VehicleModel::loadElementNames(){
	// Tags and attributes used in XML file.
	// Can't call transcode till after Xerces Initialize()

	TAG_root        = XMLString::transcode(names::sRoot);
	TAG_vehicle = XMLString::transcode(names::sVehicles);
	TAG_sensor = XMLString::transcode(names::sSensor);
	TAG_connector = XMLString::transcode(names::sConnector);
	TAG_notconnector = XMLString::transcode(names::sNotConnecotor);
	TAG_Motor = XMLString::transcode(names::sMotor);
	id = XMLString::transcode(names::sID);
	position = XMLString::transcode(names::sPosition);
	positionOne = XMLString::transcode(names::sPositionOne);
	positionTwo = XMLString::transcode(names::sPositionTwo);
	Motor = XMLString::transcode(names::sMotor);
}
void VehicleModel::loadSensors(VehicleDrawWindow* view, XMLSize_t xxx){
	try{


		// Open each sensor
		DOMNodeList*   sensors = currentVehicleElement->getElementsByTagName(TAG_sensor);
		const  XMLSize_t sensorNodeCount = sensors->getLength();
		//cout << "num sensors: " << sensors->getLength() << endl;
		for( XMLSize_t xxx = 0; xxx < sensorNodeCount; ++xxx )
		{
			DOMNode* currentsensor = sensors->item(xxx);
			DOMElement* currentsensorElement = dynamic_cast< xercesc::DOMElement* >( currentsensor );

			const XMLCh* sensorName  = currentsensorElement->getAttribute(id);
			m_OptionA = XMLString::transcode(sensorName);
			//cout << "sensor name: " << m_OptionA << endl;
			view->placing = m_OptionA;

			const XMLCh* sensorValue  = currentsensorElement->getAttribute(position);
			m_OptionB = XMLString::transcode(sensorValue);
			//cout << "sensor value: " << m_OptionB << endl;
			string newPosition = m_OptionB;
			istringstream buffer(newPosition);
			int some_int;
			buffer >> some_int;
			view->addShape(view->snapPoints.at(some_int));
		}
	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		ostringstream errBuf;
		errBuf << "Error parsing file: " << message << flush;
		XMLString::release( &message );
	}
}

void VehicleModel::loadConnectors(VehicleDrawWindow* view, XMLSize_t xxx){
	try{
		// Open each connector
		DOMNodeList*   connectors = currentVehicleElement->getElementsByTagName(TAG_connector);
		const  XMLSize_t connectorNodeCount = connectors->getLength();
		cout << "num connectors: " << connectors->getLength() << endl;
		for( XMLSize_t xxx = 0; xxx < connectorNodeCount; ++xxx )
		{
			DOMNode* currentconnector = connectors->item(xxx);
			DOMElement* currentconnectorElement = dynamic_cast< xercesc::DOMElement* >( currentconnector );

			const XMLCh* connectorName  = currentconnectorElement->getAttribute(id);
			m_OptionA = XMLString::transcode(connectorName);
			cout << "connector name: " << m_OptionA << endl;
			view->placing = m_OptionA;

			const XMLCh* connectorOne  = currentconnectorElement->getAttribute(positionOne);
			m_OptionB = XMLString::transcode(connectorOne);

			string sp1 = m_OptionB;
			istringstream buffer(sp1);
			int p1;
			buffer >> p1;
			cout << "p1: " << p1 << endl;
			int pindex1;
			for(int i=0; i < view->snapPoints.size(); i++){
				Point2D p = view->snapPoints.at(i);
				if(p.pointNumber == p1){
					pindex1 = i;
				}
			}
			const XMLCh* connectorTwo  = currentconnectorElement->getAttribute(positionTwo);
			m_OptionC = XMLString::transcode(connectorTwo);

			string sp2 = m_OptionC;
			istringstream buffer2(sp2);
			int p2;
			buffer2 >> p2;
			cout << "p2: " << p2 << endl;
			int pindex2;
			for(int i=0; i < view->snapPoints.size(); i++){
				Point2D p = view->snapPoints.at(i);
				if(p.pointNumber == p2){
					pindex2 = i;
				}
			}
			vector<LineSegment> newShape;
			newShape.push_back(LineSegment(view->snapPoints.at(pindex1).getX() , view->snapPoints.at(pindex1).getY() , view->snapPoints.at(pindex2).getX(), view->snapPoints.at(pindex2).getY(), view->snapPoints.at(pindex1).pointNumber, view->snapPoints.at(pindex2).pointNumber));
			view->shapes.push_back(Shape(newShape,Point2D(0,0,FL_BLACK ,1,0),view->placing));


		}
	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		ostringstream errBuf;
		errBuf << "Error parsing file: " << message << flush;
		XMLString::release( &message );
	}
}

void VehicleModel::loadMotors(VehicleDrawWindow* view , XMLSize_t xxx){
	try{
		// Open each Motor
		DOMNodeList*   Motors = currentVehicleElement->getElementsByTagName(TAG_Motor);
		const  XMLSize_t MotorNodeCount = Motors->getLength();
		cout << "num Motors: " << Motors->getLength() << endl;
		for( XMLSize_t xxx = 0; xxx < MotorNodeCount; ++xxx )
		{
			DOMNode* currentMotor = Motors->item(xxx);
			DOMElement* currentMotorElement = dynamic_cast< xercesc::DOMElement* >( currentMotor );

			view->placing = names::sMotor;

			const XMLCh* MotorValue  = currentMotorElement->getAttribute(position);
			m_OptionB = XMLString::transcode(MotorValue);
			cout << "sensor value: " << m_OptionB << endl;
			string newPosition = m_OptionB;
			istringstream buffer(newPosition);
			int some_int;
			buffer >> some_int;
			view->addShape(view->snapPoints.at(some_int));

		}
	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		ostringstream errBuf;
		errBuf << "Error parsing file: " << message << flush;
		XMLString::release( &message );
	}
}