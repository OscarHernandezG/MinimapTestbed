#include "j1App.h"
#include "Defs.h"
#include "p2Log.h"
#include "Entity.h"
#include "j1Collision.h"
#include "j1Particles.h"
#include "j1Render.h"

Entity::Entity(float x, float y, int type) : position(x, y), startPos(x, y) { this->type = type; }

Entity::~Entity()
{
	if (collider != nullptr)
		collider->toDelete = true;
}

const Collider* Entity::GetCollider() const
{
	return collider;
}

void Entity::Draw(SDL_Texture* sprites)
{
	//if (animation != nullptr)
	SDL_Rect rect = { 0,80,80,80 };
		App->render->Blit(sprites, position.x, position.y, &rect);
}

void Entity::OnCollision(Collider* c1, Collider* c2) {}
