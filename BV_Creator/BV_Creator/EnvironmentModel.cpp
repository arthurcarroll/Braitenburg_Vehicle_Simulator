#include "StdAfx.h"
#include "EnvironmentModel.h"
#include "EnvironmentDrawWindow.h"
#include <string>
#include <iostream>

using namespace std;
using namespace xercesc;

EnvironmentModel::EnvironmentModel(void)
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
	this->loadElementNames();
}

EnvironmentModel::~EnvironmentModel(void)
{
}

void EnvironmentModel::save(vector<Shape> shapes, string filename){
	ofstream myfile;

	if(filename.length() == 0){
		return;
	}
	myfile.open (filename.c_str());
	myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	myfile << "<" << names::sRoot << ">" << endl;
	for(int i =0; i< shapes.size(); i++){
		Shape s = shapes.at(i);
		cout << "writing vehicle: " + s.vehicleName << endl;
		if(s.name == names::sVehicles){
			ifstream infile (s.vehicleName.c_str());
			if (infile.is_open())
			{
				bool first = true;
				int skip = 0;
				while (! infile.eof() )
				{	string tempFileName;
				getline (infile,tempFileName);
				string root(names::sRoot);
				
				string docCloseTag = "</" + root + ">";
				if(skip++ > 1 && tempFileName != docCloseTag){
					if(first){

						string px(names::sPositionX);
						string py(names::sPositionY);
						
						string positionXLabel =" " + px + "=\"";
						string positionYLabel = " " + py + "=\"";

						stringstream positionXOut;
						stringstream positionYOut;

						positionXOut << s.location.getX();
						positionYOut << s.location.getY();

						string positionXValue = positionXOut.str();
						string positionYValue = positionYOut.str();

						string closingQuote = "\" ";

						string finalPosition = positionXLabel + positionXValue + closingQuote + positionYLabel+positionYValue + closingQuote;


						tempFileName.insert(tempFileName.length()-1,finalPosition);
						myfile << tempFileName << endl;
						first = false;
					}else{
						myfile << tempFileName << endl;
					}
				}
				}

			}
		}

	}
	for(int i =0; i< shapes.size(); i++){
		Shape s = shapes.at(i);
		if(s.name == names::sBox || s.name == names::sCircle){
			myfile << "<" << names::sObstacle << " " << names::sID << "=\"" << s.name << "\" " << names::sPositionX <<"=\"" << 
				s.location.getX() <<"\" "<< names::sPositionY << "=\"" << s.location.getY() <<"\" " ">";
			myfile << "</" << names::sObstacle << ">" << endl;
		}else{
			if(s.name != names::sVehicles){
				myfile << "<" << names::sStimuli << " " << names::sID << "=\"" << s.name << "\" " << names::sPositionX << "=\"" << 
					s.location.getX() <<"\" "<< names::sPositionY << "=\"" << s.location.getY() <<"\" " ">";
				myfile << "</" << names::sStimuli << ">" << endl;
			}
		}
	}
	myfile << "</" << names::sRoot <<">" << endl;
	myfile.close();

}
void EnvironmentModel::load(EnvironmentDrawWindow *view , string configFile ){
	// Test to see if the file is ok.

	struct stat fileStatus;

	int iretStat = stat(configFile.c_str(), &fileStatus);
	if( iretStat == ENOENT )
		throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
	else if( iretStat == ENOTDIR )
		throw ( std::runtime_error("A component of the path is not a directory."));
	//else if( iretStat == ELOOP )
	//throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
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

	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		ostringstream errBuf;
		errBuf << "Error parsing file: " << message << flush;
		XMLString::release( &message );
	}


	/******************************************************************
	*******************************************************************
	ACTUAL PARSING STARTS
	*******************************************************************
	******************************************************************/
	loadObjects(view , TAG_obstacle);
	loadObjects(view , TAG_stimuli);
	loadObjects(view , TAG_vehicle);
	view->redraw();

}

void EnvironmentModel::loadElementNames(){
	TAG_root        = XMLString::transcode(names::sRoot);
	TAG_vehicle = XMLString::transcode(names::sVehicles);
	TAG_obstacle = XMLString::transcode(names::sObstacle);
	TAG_stimuli = XMLString::transcode(names::sStimuli);
	id = XMLString::transcode(names::sID);
	positionX = XMLString::transcode(names::sPositionX);
	positionY = XMLString::transcode(names::sPositionY);
}
void EnvironmentModel::loadObjects(EnvironmentDrawWindow *view , XMLCh* type){
	// Get the top-level element: NAme is "root". No attributes for "root"
	DOMElement* elementRoot = xmlDoc->getDocumentElement();
	if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));

	elements = elementRoot->getElementsByTagName(type);
	const  XMLSize_t nodeCount = elements->getLength();
	cout << "num elements: " << elements->getLength() << endl;
	for( XMLSize_t xxx = 0; xxx < nodeCount; ++xxx )
	{
		currentNode = elements->item(xxx);
		currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );

		const XMLCh* pXstring  = currentElement->getAttribute(positionX);
		m_OptionA = XMLString::transcode(pXstring);
		//cout << "sensor value: " << m_OptionB << endl;
		string newXPosition = m_OptionA;
		istringstream bufferX(newXPosition);
		int pXint;
		bufferX >> pXint;

		const XMLCh* pYstring  = currentElement->getAttribute(positionY);
		m_OptionA = XMLString::transcode(pYstring);
		//cout << "sensor value: " << m_OptionB << endl;
		string newYPosition = m_OptionA;
		istringstream bufferY(newYPosition);
		int pYint;
		bufferY >> pYint;

		if(type == TAG_vehicle){
			view->placing = names::sVehicles;
			view->shapes.push_back(Shape(Point2D(pXint,pYint, 0 , 5 , 1),view->placing , ""));
		}else{
			const XMLCh* obstacleName  = currentElement->getAttribute(id);
			m_OptionA = XMLString::transcode(obstacleName);
			cout << "sensor name: " << m_OptionA << endl;
			view->placing = m_OptionA;
			view->shapes.push_back(Shape(Point2D(pXint,pYint, 0 , 5 , 1),view->placing , ""));
			cout << "added obstacle" << endl;
		}
	}
}
void EnvironmentModel::loadVehicles(EnvironmentDrawWindow *view){

}
