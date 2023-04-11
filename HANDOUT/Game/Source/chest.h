#ifndef __CHEST_H__
#define __CHEST_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class Chest : public Entity
{
public:

	Chest();
	virtual ~Chest();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

public:


private:

	SDL_Texture* texture;
	const char* texturePath;

	PhysBody* pbody;
	
	//TODO 02: Spatial audio
	//- Initialize Fx

};

#endif // __CHEST_H__