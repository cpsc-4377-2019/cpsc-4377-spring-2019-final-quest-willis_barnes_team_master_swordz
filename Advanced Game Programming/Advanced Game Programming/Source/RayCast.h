#pragma once
#ifndef RAYCAST_H
#define RAYCAST_H

#include "Box2D.h"

class RayCastCallBack : public b2RayCastCallback
{
public:
	RayCastCallBack();

	float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

	b2Fixture* fixture;
	b2Vec2 point;
	b2Vec2 normal;
	float32 fraction;

};

#endif