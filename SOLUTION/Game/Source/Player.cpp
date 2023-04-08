#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Window.h"
#include "EntityManager.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");

}

Player::~Player() {

}

bool Player::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	width = parameters.attribute("width").as_int();
	height = parameters.attribute("height").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	pbody = app->physics->CreateRectangle(position.x + width/2, position.y + height/2, width - 4, height - 4, bodyType::DYNAMIC);
	pbody->body->SetFixedRotation(true);
	pbody->listener = this;
	pbody->ctype = ColliderType::PLAYER;

	alive = true; 

	//ANIMATIONS
	
	rightIdle.PushBack({ 0, 0 * height, width, height });
	downIdle.PushBack({ 0, 1 * height, width, height });
	leftIdle.PushBack({ 0, 2 * height, width, height });
	upIdle.PushBack({ 0, 3 * height, width, height });

	//Right
	for (int i = 0; i < 4; i++) {
		rightWalk.PushBack({i * width, 0 * height, width, height});
	}
	rightWalk.speed = 0.3f;
	rightWalk.loop = true;

	//Down
	for (int i = 0; i < 4; i++) {
		downWalk.PushBack({ i * width, 1 * height, width, height });
	}
	downWalk.speed = 0.3f;
	downWalk.loop = true;

	//Left
	for (int i = 0; i < 4; i++) {
		leftWalk.PushBack({ i * width,  2 * height, width, height });
	}
	leftWalk.speed = 0.3f;
	leftWalk.loop = true;

	//Up
	for (int i = 0; i < 4; i++) {
		upWalk.PushBack({ i * width, 3 * height, width, height });
	}
	upWalk.speed = 0.3f;
	upWalk.loop = true;

	currentAnim = &downIdle;

	return true;
}

bool Player::Update()
{
	
	Move();

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	currentAnim->Update();
	
	position.x = METERS_TO_PIXELS((pbody->body->GetTransform().p.x) - width / 2);
	position.y = METERS_TO_PIXELS((pbody->body->GetTransform().p.y) - height / 2);
	
	app->render->DrawTexture(texture, position.x, position.y, &rect);

	return true;
}

bool Player::CleanUp()
{
	return true;
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype) {
	case ColliderType::RIVER_TRIGGER:
		//app->audio->PlayMusic();

		break;
	case ColliderType::UNKNOWN:
		break;
	}
}


bool Player::IsAlive() {
	return alive; 
}


void Player::Move() {

	float speed = 3;

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		vel = b2Vec2(-speed, pbody->body->GetLinearVelocity().y);
		facing = DIRECTION::LEFT;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		vel = b2Vec2(speed, pbody->body->GetLinearVelocity().y);
		facing = DIRECTION::RIGHT;
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		vel = b2Vec2(pbody->body->GetLinearVelocity().x, -speed);
		facing = DIRECTION::UP;
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		vel = b2Vec2(pbody->body->GetLinearVelocity().x, speed);
		facing = DIRECTION::DOWN;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP || 
		app->input->GetKey(SDL_SCANCODE_D) == KEY_UP || 
		app->input->GetKey(SDL_SCANCODE_W) == KEY_UP || 
		app->input->GetKey(SDL_SCANCODE_S) == KEY_UP) {

		vel = b2Vec2(0, 0);
	}



	if (facing == DIRECTION::RIGHT && vel.x == 0 && vel.y == 0) {
		currentAnim = &rightIdle;
	}

	if (facing == DIRECTION::RIGHT && vel.x != 0) {
		currentAnim = &rightWalk;
	}

	if (facing == DIRECTION::DOWN && vel.x == 0 && vel.y == 0) {
		currentAnim = &downIdle;
	}
	
	if (facing == DIRECTION::DOWN && vel.y != 0) {
		currentAnim = &downWalk;
	}

	if (facing == DIRECTION::LEFT && vel.x == 0 && vel.y == 0) {
		currentAnim = &leftIdle;
	}

	if (facing == DIRECTION::LEFT && vel.x != 0) {
		currentAnim = &leftWalk;
	}

	if (facing == DIRECTION::UP && vel.x == 0 && vel.y == 0) {
		currentAnim = &upIdle;
	}

	if (facing == DIRECTION::UP && vel.y != 0) {
		currentAnim = &upWalk;
	}

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);
}
