#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "PQueue.h"
#include "DynArray.h"

#define COST_MAP_SIZE 500

#include "PugiXml\src\pugixml.hpp"

struct TileSet
{
	SString	name;
	int	firstgid;
	int margin;
	int	spacing;
	int	tileWidth;
	int	tileHeight;
	int columns;
	int tilecount;

	SDL_Texture* texture;

	SDL_Rect GetTileRect(int gid) const;
};

struct Properties
{
	struct Property
	{
		SString name;
		bool value;
	};

	~Properties()
	{
		ListItem<Property*>* item;
		item = list.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}

		list.Clear();
	}

	Property* GetProperty(const char* name);

	List<Property*> list;
};

struct MapLayer
{
	SString	name;
	int id; 
	int width;
	int height;
	uint* data;

	Properties properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		return data[(y * width) + x];
	}
};

struct MapData
{
	int width;
	int	height;
	int	tileWidth;
	int	tileHeight;
	List<TileSet*> tilesets;

	// L05: DONE 2: Add a list/array of layers to the map
	List<MapLayer*> maplayers;
};

enum ColTypes {

	UNKNOWN = -1,
	TERRAIN,

};

struct ColData
{
	int x;
	int	y;
	int width;
	int	height;
	ColTypes type;
};

class Map : public Module
{
public:

	Map();

	// Destructor
	virtual ~Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load();

	// L05: DONE 8: Create a method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;

	iPoint Map::WorldToMap(int x, int y);

private:

	bool LoadMap(pugi::xml_node mapFile);

	// L04: DONE 4: Create and call a private function to load a tileset
	bool LoadTileSet(pugi::xml_node mapFile);

	// L05
	bool LoadColliders(pugi::xml_node& node);
	void CreateColliders(ColData colliders);

	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadAllLayers(pugi::xml_node mapNode);

	// L06: DONE 2
	TileSet* GetTilesetFromTileId(int gid) const;

	// L06: DONE 6: Load a group of properties 
	bool LoadProperties(pugi::xml_node& node, Properties& properties);

public:

	MapData mapData;

private:

	SString mapFileName;
	SString mapFolder;
	bool mapLoaded;

};

#endif // __MAP_H__