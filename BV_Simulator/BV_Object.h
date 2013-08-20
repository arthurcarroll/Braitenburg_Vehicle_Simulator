#pragma once
#include "stdafx.h"


class BV_Object
{
public:
	BV_Object(void);
	~BV_Object(void);
	irr::scene::IAnimatedMesh *mesh;
	irr::scene::ISceneNode *node;
};
