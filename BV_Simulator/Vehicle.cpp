#include "StdAfx.h"
#include "Vehicle.h"
#include <cmath>

using namespace irr;
using namespace std;

irr::scene::ISceneNode *testNode;

Vehicle::Vehicle(scene::ISceneManager* smgr, float x, float y, float z)
{
	mesh = smgr->getMesh("../models/vehicle/vehicle.mesh");
	node = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 512);
	node->setScale(core::vector3df(10,10,10));
	node->setPosition(core::vector3df(x,y,z));
	this->load(smgr);
	this->firstUpdate = true;
	lastRotation = 0;
}

Vehicle::~Vehicle(void)
{
}

void Vehicle::update(u32 time, std::vector<Stimuli> stims){
	float deltaT;
	if(firstUpdate){
		deltaT = 1;
		firstUpdate = false;
	}else{
		
		deltaT = time - prevTime;
		if(deltaT > 40){
			deltaT = 1;
		}
	}
	float totalVelocity = 0;
	float totalRotation = node->getRotation().Y;
	
	
	// for each stimuli
	for(int i=0; i<stims.size(); i++){
		// for each connector
		for(int j=0; j < connectors.size(); j++){
			Connector* c  = connectors.at(j);
			Sensor* s = c->sensor;
			Motor* a = c->actuator;

			// if stimuli matches sensor
			if( s->stimuli.compare(stims.at(i).name) == 0){
				irr::scene::ISceneNode* currentSensor= s->node;
				irr::scene::ISceneNode* currentStimuli= stims.at(i).node;
				irr::f32 distance = currentSensor->getAbsolutePosition().getDistanceFrom(currentStimuli->getAbsolutePosition());
				
				if(distance < 500){
					float pull = (stims.at(i).strength)/(pow(distance,2));
					
					float sensorRangeMin = 0;
					float sensorRangeMax = 500;

					float turnRadiusMin = 0;
					float turnRadiusMax = 5000 * deltaT;
					
   					float sensorRange = (sensorRangeMax - sensorRangeMin);
					float turnRadiusRange = (turnRadiusMax - turnRadiusMin);
					float turnAngle = (((pull - sensorRangeMin) * turnRadiusRange) / sensorRange) + turnRadiusMin;
					if(a->side.compare("left")==0){
						//totalRotation-=turnAngle*10;
						totalRotation-=turnAngle;
					}else{
						//totalRotation+=turnAngle*10;
						totalRotation+=turnAngle;
						//std::cout <<  a->node->getRelativeTransformation();
					}
				
					float velocity = turnAngle*.8f;
					totalVelocity-=velocity;
				}

			}
		}
	}
	//cout << "  testX: " << testNode->getAbsolutePosition().X <<"  turn angle: " << totalRotation << " velocity: " << totalVelocity << " deltaT: " << deltaT <<endl;
	node->setRotation(core::vector3df(0,totalRotation,0));
	//move(node,core::vector3df(0,0,totalVelocity/100));
	move(node,core::vector3df(0,0,totalVelocity/50));
	prevTime = time;
}

void Vehicle::load(irr::scene::ISceneManager* smgr){
	// frontLeft
	motors.push_back(new Motor(smgr,this->node, core::vector3df(0.44f,0.15f,-0.3f),"../models/tires/tireRight.mesh", "left"));
	// frontRight
	motors.push_back(new Motor(smgr,this->node, core::vector3df(-0.44f,0.15f,-0.3f),"../models/tires/tireLeft.mesh", "right"));
  	// rearLeft
	motors.push_back(new Motor(smgr,this->node, core::vector3df(0.44f,0.15f,0.3f),"../models/tires/tireRight.mesh", "left"));
	// rearRight
	motors.push_back(new Motor(smgr,this->node, core::vector3df(-0.44f,0.15f,0.3f),"../models/tires/tireLeft.mesh", "right"));
	
	// front right sensor
	sensors.push_back(new Sensor(smgr,this->node,core::vector3df(0.3f,0.15f,-0.40),"../models/sensors/sensorRight.mesh","light","right")); 
	
	// front left sensor
	sensors.push_back(new Sensor(smgr,this->node,core::vector3df(-0.3f,0.15f,-0.40),"../models/sensors/sensorLeft.mesh", "light","left"));
	
	// test empty node
	irr::scene::IAnimatedMesh *mesh = smgr->getMesh("../models/emptyNodeTest/emptyNodeTest.mesh");
	testNode = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 512);
	
	testNode->setPosition(core::vector3df(1.0f,0.0f,-1.0f));
	testNode->setScale(core::vector3df(0.2f,0.2f,0.2f));
	testNode->setParent(this->node);


	// connect sensors to motors, note that each sensor and actuator can belong to more that one connector
	connectors.push_back(new Connector(motors.at(0),sensors.at(0),true));
	connectors.push_back(new Connector(motors.at(1),sensors.at(1),true));

}

//--- move acording to rotation --- 
void Vehicle::move(irr::scene::ISceneNode *node, //node to move 
				   irr::core::vector3df vel) //velocity vector 
				   // for example to move node 10 units forward use vector3df(0,0,10) 
{ 
	irr::core::matrix4 m; 
	m.setRotationDegrees(node->getRotation()); 
	m.transformVect(vel); 
	node->setPosition(node->getPosition() + vel); 
	node->updateAbsolutePosition(); 
} 