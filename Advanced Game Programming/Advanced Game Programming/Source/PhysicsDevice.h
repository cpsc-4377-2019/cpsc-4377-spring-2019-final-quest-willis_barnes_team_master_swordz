#pragma once
#ifndef PHYSICSDEVICE_H
#define PHYSICSDEVICE_H

#include <memory>
#include "Box2d.h"
#include "ObjectFactory.h"
#include "Definitions.h"

class BodyComponent;
class ContactListener;
class RayCastCallBack;

class PhysicsDevice {
public:
	PhysicsDevice();
	~PhysicsDevice();

	bool update(float dt);
	bool createFixture(BodyComponent* object, BodyInitializer);
	bool createJoint(Joints joint);
	bool removeObject(BodyComponent* object);

	bool setTransform(BodyComponent* object, Position pos, EngineFloat angle);
	bool setLinearVelocity(BodyComponent* object, Position linearVelociy);
	bool setAngularVelocity(const BodyComponent* object, EngineFloat angularVelocity);
	bool setTorque(const BodyComponent* object, EngineFloat torque);
	bool setLinearImpulse(const BodyComponent* object, Position forceVec, Position forceCenter);
	bool setStatic(const BodyComponent* object);
	bool setStopPhysics(const BodyComponent* object);
	bool setAngle(const BodyComponent* object, EngineFloat angle);
	bool accelerate(const BodyComponent* object, Position forceVec);

	Object* RayCast(BodyComponent* object, Position target);
	b2Vec2 normalize(b2Vec2 vec);

	EngineFloat getAngularVelocity(BodyComponent* object) const;
	Position getPosition(BodyComponent* object) const;
	EngineFloat getAngle(const BodyComponent* object) const;
	Position getVelocity(const BodyComponent* object) const;
	Position getLinearVelocity(const BodyComponent* object) const;

private:

	b2Body* FindBody(const BodyComponent* bodyComponent) const;

	inline float PW2RW(EngineFloat x)const { return x * fPRV; }
	inline float RW2PW(EngineFloat x)const { return x / fPRV; }
	inline float RW2PW(int x)const { return (float)x / fPRV; }
	inline float RW2PWAngle(EngineFloat x)const { return((float)x*(2.0f*3.14159f) / 360.0f); } //degrees to radians
	inline float PW2RWAngle(EngineFloat x)const { return((float)x*360.0f / (2.0f*3.14159f)); } //radians to degrees
	b2Vec2 GV2PV(Position gameVec)const;
	Position PV2GV(b2Vec2 physicsVec)const;
	Position alignCenters(BodyComponent* object)const;

	bool destroyJoint(BodyComponent* object);
	bool destroyJoint(b2Body* body);

	std::unique_ptr<b2World> world{ nullptr };
	std::unique_ptr<ContactListener> c1{ nullptr };
	const b2Vec2 gravity{ 0,0 };
	static const float fPRV;


};

#endif