#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> collider1;

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* general;

	//background
	SDL_Rect background;

	//ball
	PhysBody* ball;

	//spring
	PhysBody* spring;
	SDL_Texture* spring_text;

	//stop spring
	PhysBody* stop1;
	PhysBody* stop2;

	//left flippers

	SDL_Texture* flip_l;
	SDL_Texture* flip_r;

	//sensors
	PhysBody* respawn_sensor;
	p2List<PhysBody*> Sensors;

	//life
	uint lives = 3;
	SDL_Texture* loselife;


	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
};
