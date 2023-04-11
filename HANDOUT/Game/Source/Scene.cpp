#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	for (pugi::xml_node itemNode = config.child("chest"); itemNode; itemNode = itemNode.next_sibling("chest"))
	{
		Chest* chest = (Chest*)app->entityManager->CreateEntity(EntityType::CHEST);
		chest->parameters = itemNode;
	}

	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	player->parameters = config.child("player");

	//TODO 02: Playlist
	//- Load tracks from config

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	//Load map
	bool retLoad = app->map->Load();
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	//Set the window title with map/tileset info
	SString title("Music and Audio Manager");
	app->win->SetTitle(title.GetString());

	//TODO 04: Playlist
	//- Start playlist

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	//TODO 04: Playlist
	//- Call functions on key press
	if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
		
	}
	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		
	}

	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
