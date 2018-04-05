#include"Brofiler\Brofiler.h"

#include "Defs.h"
#include "p2Log.h"

#include "j1App.h"

#include "j1Input.h"
#include "j1Textures.h"
#include "j1FadeToBlack.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Particles.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1EntityFactory.h"
#include "j1Pathfinding.h"
#include "j1Gui.h"

#include "UILabel.h"
#include "UIButton.h"
#include "UIImage.h"
#include "UICursor.h"


j1Scene::j1Scene() : j1Module()
{
	name.assign("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	bool ret = true;

	LOG("Loading scene");

	// Load maps
	pugi::xml_node maps = config.child("maps");

	orthogonalMap = maps.child("orthogonal").attribute("name").as_string();
	orthogonalActive = maps.child("orthogonal").attribute("active").as_bool();
	orthogonalTexName = maps.child("orthogonal").attribute("tex").as_string();

	isometricMap = maps.child("isometric").attribute("name").as_string();
	isometricActive = maps.child("isometric").attribute("active").as_bool();
	isometricTexName = maps.child("isometric").attribute("tex").as_string();

	warcraftMap = maps.child("warcraft").attribute("name").as_string();
	warcraftActive = maps.child("warcraft").attribute("active").as_bool();
	warcraftTexName = maps.child("warcraft").attribute("tex").as_string();

	isF2Pressed = false;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	bool ret = false;

	// Save camera info
	App->win->GetWindowSize(width, height);
	scale = App->win->GetScale();

	// Load an orthogonal, isometric or warcraft-based map
	if (orthogonalActive) {
		ret = App->map->Load(orthogonalMap.data());
		debugTex = App->tex->Load(orthogonalTexName.data());
	}
	else if (isometricActive) {
		ret = App->map->Load(isometricMap.data());
		debugTex = App->tex->Load(isometricTexName.data());
	}
	else if (warcraftActive) {
		ret = App->map->Load(warcraftMap.data());
		debugTex = App->tex->Load(warcraftTexName.data());
	}

	// Create walkability map
	if (ret)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}


	//TODO 3 Create the minimap in the scene (UIMinimap* minimap)
	/// For the minimap info (SDL_Rect minimapInfo) 32 for x and y and 200 for width and height are good values
	/// The entity width and height can be the same as one tile (32)

	return ret;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	bool ret = true;

	// debug pathfing ------------------
	static iPoint origin;
	static bool isSelected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);


return ret;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	bool ret = true;

	// Draw
	App->map->Draw(); // map
	App->entities->Draw(); // entities

	if (minimap)
		minimap->Update(dt);

	// Debug pathfinding ------------------------------

	int x = 0, y = 0;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	const vector<iPoint>* path = App->pathfinding->GetLastPath();

	// F1, F2, F3, F4, F5, F6, +, -
	DebugKeys();

	int downMargin = -(App->map->data.height * App->map->data.tileHeight) + height / scale;
	int rightMargin = -(App->map->data.width * App->map->data.tileWidth) + width / scale;

	int	camSpeed = 300;


	//Move with arrows
	//UP
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && App->render->camera.y <= 0)
		App->render->camera.y += camSpeed * dt;
	//DOWN
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && App->render->camera.y >= downMargin)
		App->render->camera.y -= camSpeed * dt;
	//LEFT
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && App->render->camera.x <= 0)
		App->render->camera.x += camSpeed * dt;
	//RIGHT
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && App->render->camera.x >= rightMargin)
		App->render->camera.x -= camSpeed * dt;
	
	
//Minimap
//------------------------------------------------------------
	///TODO 4 Bonus code: Uncomment this code to spawn entities and add them to the minimap
		/*
		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		{
			if (!isF2Pressed)
				if (minimap)
				{
					minimap->AddEntity(App->entities->AddUnit(400, 600, 0));
					minimap->AddEntity(App->entities->AddUnit(500, 600, 0));
					minimap->AddEntity(App->entities->AddUnit(600, 600, 0));
					isF2Pressed = true;
				}
		}

		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
		{
			if (minimap != nullptr)
			{
				int x, y;
				App->input->GetMousePosition(x, y);
				iPoint mousePos = App->render->ScreenToWorld(x, y);

				minimap->AddEntity(App->entities->AddUnit(mousePos.x, mousePos.y, 0));
			}
		}
		*/
	

	return ret;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	bool ret = true;

	LOG("Freeing scene");

	App->audio->PauseMusic();
	App->map->UnLoad();
	App->tex->UnLoad(debugTex);

	// Set to nullptr the pointers to the UI elements

	return ret;
}

// Debug keys
void j1Scene::DebugKeys()
{
	// F1: start from the beginning of the first level
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		/*
		if (index == 0)
			App->entities->playerData->position = App->entities->playerData->startPos;
		else
			index = 0;

		App->fade->FadeToBlack(this, this, FADE_LESS_SECONDS, FADE_TYPE::FADE_TYPE_SLIDE);
		*/
	}

	// F2: start from the beginning of the current level
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		/*
		App->fade->FadeToBlack(this, this, FADE_LESS_SECONDS, FADE_TYPE::FADE_TYPE_SLIDE);
		*/
	}

	// F4: change between maps
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		/*
		if (index == 0)
			index = 1;
		else
			index = 0;

		App->fade->FadeToBlack(this, this, FADE_LESS_SECONDS, FADE_TYPE::FADE_TYPE_SLIDE);
		*/
	}

	// F5: save the current state
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		App->SaveGame();
	}

	// F6: load the previous state
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		App->LoadGame();
	}

	// F7: fullscreen
	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) {
		if (App->win->fullscreen) {
			App->win->fullscreen = false;
			SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_SHOWN);
		}
		else {
			App->win->fullscreen = true;
			SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
	}

	// F10: God mode
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		god = !god;

	// 1, 2, 3: camera blit
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && App->map->blitOffset < 15 && App->map->cameraBlit)
		App->map->blitOffset += 7;

	else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && App->map->blitOffset > -135 && App->map->cameraBlit)
		App->map->blitOffset -= 7;

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		App->map->cameraBlit = !App->map->cameraBlit;
}

void j1Scene::OnUIEvent(UIElement* UIelem, UI_EVENT UIevent)
{
	switch (UIevent)
	{
	case UI_EVENT_MOUSE_ENTER:

		break;

	case UI_EVENT_MOUSE_LEAVE:

		break;

	case UI_EVENT_MOUSE_LEFT_CLICK:

		break;

	case UI_EVENT_MOUSE_LEFT_UP:

		break;
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

// Save
bool j1Scene::Save(pugi::xml_node& save) const
{
	bool ret = true;

	/*
	if (save.child("gate") == NULL) {
	save.append_child("gate").append_attribute("opened") = gate;
	save.child("gate").append_attribute("fx") = fx;
	}
	else {
	save.child("gate").attribute("opened") = gate;
	save.child("gate").attribute("fx") = fx;
	}
	*/

	return ret;
}

// Load
bool j1Scene::Load(pugi::xml_node& save)
{
	bool ret = true;

	/*
	if (save.child("gate") != NULL) {
	gate = save.child("gate").attribute("opened").as_bool();
	fx = save.child("gate").attribute("fx").as_bool();
	}
	*/

	return ret;
}