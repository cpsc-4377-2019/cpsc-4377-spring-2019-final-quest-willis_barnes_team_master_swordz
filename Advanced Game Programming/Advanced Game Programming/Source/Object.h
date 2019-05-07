#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <memory>
#include <vector>
#include "SDL.h"
#include "ObjectFactory.h"
#include "Definitions.h"

class Components;
class View;
class Texture;
class InputDevice;

class Object{
    public:
        Object();
        ~Object();
		void addComponent(Components*);
		bool Initialize();
		std::unique_ptr<Object> update();
		void draw(View*);
		template<class T>
		T* getComponent() const
		{
			for (auto& component : components)
			{

				if (T* target = nullptr; target = dynamic_cast<T*>(component.get()))
				{
					return(target);
				}
			}
			return(nullptr);
		}

		ObjectType getType();
		void setType(ObjectType);

		bool getIsDead();
		void setIsDead(bool);

    protected:
		std::vector<std::unique_ptr<Components>> components;

		ObjectType type;
		bool isDead;
};

#endif