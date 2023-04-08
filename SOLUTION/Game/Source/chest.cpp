#include "Chest.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

Chest::Chest() : Entity(EntityType::CHEST)
{
	name.Create("chest");
}

Chest::~Chest() {}

bool Chest::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Chest::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	
	pbody = app->physics->CreateRectangle(position.x, position.y,8,8, bodyType::STATIC);
	shimmerFX = app->audio->LoadFx("Assets/Audio/Fx/chestShimmer1.wav");

	pbody->ctype = ColliderType::CHEST; 
	pbody->listener = this;

	return true;
}

bool Chest::Update()
{
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x);
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y);

	app->render->DrawTexture(texture, position.x - 4, position.y - 4);

	app->audio->PlaySpatialFx(shimmerFX,0, (Entity*)this, (Entity*)app->scene->player, 20, 120);
	
	return true;
}

bool Chest::CleanUp()
{
	return true;
}

void Chest::OnCollision(PhysBody* physA, PhysBody* physB) {

}