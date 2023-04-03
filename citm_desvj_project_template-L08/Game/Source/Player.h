#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Path.h"
#include "Physics.h"

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	bool IsAlive(); 
	
	void Move(); 

public:

	PhysBody* pbody;

	bool alive = false;

private:

	SDL_Texture* texture;
	const char* texturePath;

	int width;
	int height;

	b2Vec2 vel; 

	DIRECTION facing = DIRECTION::RIGHT;

	Animation* currentAnim = nullptr;

	Animation rightIdle;
	Animation leftIdle;
	Animation downIdle;
	Animation upIdle;

	Animation rightWalk;
	Animation leftWalk;
	Animation downWalk;
	Animation upWalk;

};

#endif // __PLAYER_H__