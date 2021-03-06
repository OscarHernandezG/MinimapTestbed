#ifndef __j1TEXTURES_H__
#define __j1TEXTURES_H__

#include <list>

#include "j1Module.h"

using namespace std;

struct SDL_Texture;
struct SDL_Surface;
struct SDL_Renderer;

class j1Textures : public j1Module
{
public:

	j1Textures();

	// Destructor
	virtual ~j1Textures();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before quitting
	bool CleanUp();

	// Load Texture
	SDL_Texture* const	Load(const char* path); 
	SDL_Texture* const	Load(const char* path, SDL_Renderer*	renderer);
	bool				UnLoad(SDL_Texture* texture);
	SDL_Texture* const	LoadSurface(SDL_Surface* surface); 
	SDL_Texture* const	LoadSurface(SDL_Surface* surface, SDL_Renderer*	renderer);
	void				GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:

	list<SDL_Texture*>	textures;
};


#endif //__j1TEXTURES_H__