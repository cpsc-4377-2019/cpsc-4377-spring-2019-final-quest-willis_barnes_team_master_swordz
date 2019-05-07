/*
	Project definitions were taken directly from Mr. Orme's Signature Experience Github repository
	https://github.com/Mr-Orme/signature.experience.engine/blob/master/Source/Definitions.h
*/

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cmath>
#include <memory>
//TODO:: const correctness. Check to see if consts can be put on pointer parameters and class methods.
//TODO:: clear out #includes. Make sure every #include is needed in ever file!
//TODO:: Move initialization to the constructor and stopping/finishing to the destructor.
//TODO:: Move default initialization of member variables to .h file using {} for ALL classes!
//Basic Types
typedef unsigned int	Uint32;
typedef float			EngineFloat;
typedef Uint32			EngineInt;

class Texture;
class GraphicsDevice;
class BodyComponent;

struct Position
{
	EngineFloat x;
	EngineFloat y;

	friend Position operator+ (const Position & src1, const Position & src2)
	{
		return { src1.x + src2.x, src1.y + src2.y };
	}
	friend Position operator- (const Position & src1, const Position & src2)
	{
		return { src1.x - src2.x, src1.y - src2.y };
	}
	friend bool operator> (const Position & src1, int src2)
	{
		if (src1.x > src2 && src1.y > src2)
		{
			return true;
		}
		return false;
	}
	friend bool operator< (const Position & src1, int src2)
	{
		if (src1.x < src2 && src1.y < src2)
		{
			return true;
		}
		return false;
	}
	friend bool operator== (const Position & src1, const Position & src2)
	{
		if (src1.x == src2.x && src1.y == src2.y)
		{
			return true;
		}
		return false;
	}
	friend Position abs(Position & src)
	{
		return { abs((float)src.x),abs((float)src.y) };
	}
};

struct RGBA
{
	EngineInt R;
	EngineInt G;
	EngineInt B;
	EngineInt A;
};

//Physics Stuff
enum class JointType{Revolute, Distance, Prismatic, Wheel, Weld, Pulley, Friction, Gear, Mouse, Rope, None};
enum class BodyType{Static, Kinematic, Dynamic};
enum class BodyShape { Rectangle, Circle };

struct Joints {
	JointType type;
	BodyComponent* bodyA;
	BodyComponent* bodyB;
	bool CollideConnected;
	Position AnchorA;
	Position AnchorB;
	EngineFloat referenceAngle;
	EngineFloat JointLimit;
};

struct PhysicsStats {
	EngineFloat spinSpeed{ 0.0f };
	BodyType bodyType{ BodyType::Dynamic };
	BodyShape bodyShape{ BodyShape::Rectangle };
	EngineFloat density{ 0.0f };
	EngineFloat friction{ 0.0f };
	EngineFloat restitution{ 0.0f };
	EngineFloat angularDamping{ 999.0f };
	EngineFloat linearDamping{ 0.0f };
	EngineFloat force{ 0.0f };
	Joints joint;
	bool physicsOn{ true };
};

//Initializers
struct BodyInitializer {
	Position pos;
	EngineFloat angle;
	PhysicsStats physics;
};

struct SpriteInitializer {
	const char* spriteName;
	std::shared_ptr<Texture> texture;
	GraphicsDevice* gDevice;
};

enum ObjectType{bullet, enemy, player, arrow, other};

//Constants
const EngineFloat PI = 3.14159f;


#endif