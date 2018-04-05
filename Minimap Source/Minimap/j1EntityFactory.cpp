#include "Defs.h"
#include "p2Log.h"

#include "j1Module.h"
#include "j1App.h"

#include "j1EntityFactory.h"
#include "j1Render.h"

#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Collision.h"

#include "Entity.h"

j1EntityFactory::j1EntityFactory()
{
	name.assign("entities");
}

// Destructor
j1EntityFactory::~j1EntityFactory()
{
}

bool j1EntityFactory::Awake(pugi::xml_node& config) {

	bool ret = true;

	pugi::xml_node spritesheets = config.child("spritesheets");

	footmanTexName = spritesheets.child("footman").attribute("name").as_string();

	return ret;
}

bool j1EntityFactory::Start()
{
	bool ret = true;

	LOG("Loading entities textures");

	footmanTex = App->tex->Load(footmanTexName.data());

	return ret;
}

bool j1EntityFactory::PreUpdate()
{
	bool ret = true;

	// Spawn entities
	list<Entity*>::const_iterator it = toSpawnEntities.begin();

	while (it != toSpawnEntities.end()) {

		// Move the entity from the waiting list to the active list
		activeEntities.push_back(*it);

		
		int x = (*it)->startPos.x * App->scene->scale;
		int y = (*it)->startPos.y * App->scene->scale;
		App->map->WorldToMap(x, y);
		LOG("Spawning entity at tile %d,%d", x, y);
		
		it++;
	}
	toSpawnEntities.clear();

	return ret;
}

// Called before render is available
bool j1EntityFactory::Update(float dt)
{
	bool ret = true;

	// Update active entities
	list<Entity*>::const_iterator it = activeEntities.begin();

	while (it != activeEntities.end()) {
		(*it)->Move(dt);
		it++;
	}
	it = activeEntities.begin();
	while (it != activeEntities.end()) {
		(*it)->Draw(footmanTex);
		it++;
	}

	return ret;
}

void j1EntityFactory::Draw()
{
	// Blit active entities
	list<Entity*>::const_iterator it = activeEntities.begin();

	while (it != activeEntities.end()) {

		switch ((*it)->type) {
		
		default:
			(*it)->Draw(footmanTex);
			break;
		
		}
		it++;
	}
}


iPoint j1EntityFactory::FindClosestWalkableTile(Entity* entity, iPoint tile) const
{
	iPoint currTile = { -1,-1 };
	//vector<iPoint> visitedTiles;

	//visitedTiles.push_back(tile);

	//while (visitedTiles.size() > 0) {

	//	currTile = visitedTiles.front();
	//	visitedTiles.erase(visitedTiles.begin());

	//	if (App->pathfinding->IsWalkable(currTile) && !IsAnotherEntityOnTile(entity, currTile))
	//		return currTile;

	//	iPoint neighbors[4];
	//	neighbors[0].create(currTile.x + 1, currTile.y + 0);
	//	neighbors[1].create(currTile.x + 0, currTile.y + 1);
	//	neighbors[2].create(currTile.x - 1, currTile.y + 0);
	//	neighbors[3].create(currTile.x + 0, currTile.y - 1);

	//	for (uint i = 0; i < 4; ++i)
	//	{
	//		if (find(visitedTiles.begin(), visitedTiles.end(), neighbors[i]) == visitedTiles.end())
	//			visitedTiles.push_back(neighbors[i]);
	//	}
	//}

	return currTile;
}

bool j1EntityFactory::PostUpdate()
{
	bool ret = true;

	// Remove entities
	list<Entity*>::const_iterator it = activeEntities.begin();

	while (it != activeEntities.end()) {
		if ((*it)->remove) {
			delete *it;
			activeEntities.remove(*it);
		}
		it++;
	}

	return ret;
}

// Called before quitting
bool j1EntityFactory::CleanUp()
{
	bool ret = true;

	LOG("Freeing all entities");

	// Remove all entities
	list<Entity*>::const_iterator it = activeEntities.begin();

	while (it != activeEntities.end()) {
		delete *it;
		it++;
	}
	activeEntities.clear();

	it = toSpawnEntities.begin();

	while (it != toSpawnEntities.end()) {
		delete *it;
		it++;
	}
	toSpawnEntities.clear();

	// Free all textures
	App->tex->UnLoad(footmanTex);

	return ret;
}

void j1EntityFactory::OnCollision(Collider* c1, Collider* c2)
{
	// Check for collisions

	list<Entity*>::const_iterator it = activeEntities.begin();

	while (it != activeEntities.end()) {
		if ((*it)->GetCollider() == c1) {
			(*it)->OnCollision(c1, c2);
			break;
		}
		it++;
	}
}

Entity* j1EntityFactory::AddUnit(float x, float y, int type)
{
	
	Entity* unit = new Entity(x, y, type);
	toSpawnEntities.push_back(unit);

	return unit;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

bool j1EntityFactory::Load(pugi::xml_node& save)
{
	bool ret = true;

	pugi::xml_node node;

	list<Entity*>::const_iterator it = activeEntities.begin();

	while (it != activeEntities.end()) {

		it++;
	}

	return ret;
}

bool j1EntityFactory::Save(pugi::xml_node& save) const
{
	bool ret = true;

	pugi::xml_node node;

	list<Entity*>::const_iterator it = activeEntities.begin();

	while (it != activeEntities.end()) {

		it++;
	}

	return ret;
}