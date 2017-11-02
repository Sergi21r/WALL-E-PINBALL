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
	PhysBody* sensor1;
	PhysBody* sensor2;
	PhysBody* sensor3;
	PhysBody* sensor4;
	PhysBody* sensor5;
	PhysBody* sensor6;
	PhysBody* sensor7;
	PhysBody* sensor8;
	PhysBody* sensor9;

	//life
	uint lives = 3;
	SDL_Texture* loselife;
	uint cont = 0;

	//score
	uint score = 0;
	uint highscore = 0;

	SDL_Texture* game_over;
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;
	uint music;
	p2Point<int> ray;
	bool ray_on;
};
