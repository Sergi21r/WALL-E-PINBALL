#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;


	App->renderer->camera.x = App->renderer->camera.y = 0;

	general = App->textures->Load("pinball/map2.png");
	circle = App->textures->Load("pinball/ball.png"); 
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	flip_l = App->textures->Load("pinball/flipper_l2.png");
	flip_r = App->textures->Load("pinball/flipper_r2.png");
	spring_text = App->textures->Load("pinball/muelle.png");
	loselife = App->textures->Load("pinball/lose_life.png");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	//CHAIN COLLIDER 1
	int chain_collider1[134] = {
		399, 618,
		399, 173,
		394, 134,
		381, 99,
		372, 79,
		358, 59,
		373, 46,
		390, 23,
		379, 14,
		363, 22,
		345, 38,
		320, 31,
		305, 24,
		280, 14,
		259, 10,
		237, 6,
		214, 10,
		202, 16,
		187, 23,
		172, 15,
		149, 12,
		123, 12,
		100, 18,
		75, 31,
		52, 45,
		38, 28,
		24, 17,
		9, 14,
		7, 29,
		17, 40,
		33, 57,
		23, 72,
		16, 87,
		9, 105,
		6, 125,
		7, 143,
		9, 160,
		17, 178,
		28, 204,
		49, 238,
		59, 257,
		4, 292,
		7, 318,
		60, 355,
		7, 387,
		13, 428,
		8, 441,
		5, 458,
		4, 498,
		5, 508,
		118, 577,
		129, 643,
		240, 643,
		254, 576,
		366, 507,
		367, 435,
		347, 417,
		362, 412,
		371, 397,
		358, 388,
		349, 378,
		360, 351,
		365, 301,
		370, 266,
		375, 264,
		376, 618,
		380, 618
	};
	PhysBody* bg;
	bg = App->physics->CreateChain(0, 0, chain_collider1, 134);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);

	//COLLIDER2
	int chain_collider2[42] = {
		249, 598,
		377, 599,
		375, 259,
		322, 323,
		317, 341,
		326, 353,
		351, 364,
		349, 371,
		348, 379,
		360, 389,
		367, 395,
		368, 402,
		360, 407,
		347, 413,
		346, 418,
		366, 436,
		369, 449,
		370, 481,
		368, 501,
		253, 577,
		251, 587
	};
	PhysBody* bg1;
	bg1 = App->physics->CreateChain(0, 0, chain_collider2, 42);
	bg1->body->SetType(b2_staticBody);
	bg1->body->GetFixtureList()->SetDensity(0.1f);

	//COLLIDER3
	int chain_collider3[12] = {
		341, 446,
		352, 453,
		350, 489,
		250, 557,
		244, 547,
		342, 480
	};
	PhysBody* bg2;
	bg2 = App->physics->CreateChain(0, 0, chain_collider3, 12);
	bg2->body->SetType(b2_staticBody);
	bg2->body->GetFixtureList()->SetDensity(0.1f);

	//COLLIDER4
	int chain_collider4[12] = {
		129, 546,
		33, 484,
		32, 450,
		23, 454,
		23, 492,
		122, 556
	};
	PhysBody* bg3;
	bg3 = App->physics->CreateChain(0, 0, chain_collider4, 12);
	bg3->body->SetType(b2_staticBody);
	bg3->body->GetFixtureList()->SetDensity(0.1f);

	//COLLIDER5
	int chain_collider5[10] = {
		315, 436,
		252, 508,
		255, 514,
		318, 471,
		320, 443
	};
	PhysBody* bg4;
	bg4 = App->physics->CreateChain(0, 0, chain_collider5, 10);
	bg4->body->SetType(b2_staticBody);
	bg4->body->GetFixtureList()->SetRestitution(0.8f);
	
	//COLLIDER6
	int chain_collider6[10] = {
		73, 451,
		113, 506,
		111, 513,
		58, 475,
		65, 454
	};
	PhysBody* bg5;
	bg5 = App->physics->CreateChain(0, 0, chain_collider6, 10);
	bg5->body->SetType(b2_staticBody);
	bg5->body->GetFixtureList()->SetRestitution(0.8f);

	//COLLIDER7
	int chain_collider7[18] = {
		157, 339,
		184, 372,
		215, 338,
		210, 333,
		197, 343,
		191, 358,
		178, 355,
		174, 345,
		160, 336
	};
	PhysBody* bg6;
	bg6 = App->physics->CreateChain(0, 0, chain_collider7, 18);
	bg6->body->SetType(b2_staticBody);
	bg6->body->GetFixtureList()->SetRestitution(1.5f);

	//COLLIDER8
	int chain_collider8[8] = {
		124, 281,
		113, 294,
		125, 304,
		135, 295
	};
	PhysBody* bg7;
	bg7 = App->physics->CreateChain(0, 0, chain_collider8, 8);
	bg7->body->SetType(b2_staticBody);
	bg7->body->GetFixtureList()->SetRestitution(0.7f);

	//COLLIDER9
	int chain_collider9[8] = {
		164, 282,
		153, 292,
		163, 305,
		175, 295
	};
	PhysBody* bg8;
	bg8 = App->physics->CreateChain(0, 0, chain_collider9, 8);
	bg8->body->SetType(b2_staticBody);
	bg8->body->GetFixtureList()->SetRestitution(0.7f);

	//COLLIDER10
	int chain_collider10[8] = {
		208, 282,
		198, 293,
		210, 305,
		220, 295
	};
	PhysBody* bg9;
	bg9 = App->physics->CreateChain(0, 0, chain_collider10, 8);
	bg9->body->SetType(b2_staticBody);
	bg9->body->GetFixtureList()->SetRestitution(0.7f);

	//COLLIDER11
	int chain_collider11[8] = {
		248, 281,
		237, 293,
		250, 307,
		261, 292
	};
	PhysBody* bg10;
	bg10 = App->physics->CreateChain(0, 0, chain_collider11, 8);
	bg10->body->SetType(b2_staticBody);
	bg10->body->GetFixtureList()->SetRestitution(0.7f);

	//COLLIDER12
	int chain_collider12[28] = {
		45, 293,
		61, 303,
		63, 319,
		68, 325,
		77, 328,
		85, 324,
		88, 315,
		93, 317,
		93, 333,
		86, 341,
		72, 338,
		53, 326,
		25, 310,
		39, 299
	};
	PhysBody* bg11;
	bg11 = App->physics->CreateChain(0, 0, chain_collider12, 28);
	bg11->body->SetType(b2_staticBody);
	bg11->body->GetFixtureList()->SetRestitution(2.0f); 

	//COLLIDER13
	int chain_collider13[60] = {
		319, 283,
		327, 272,
		354, 236,
		371, 202,
		375, 165,
		373, 128,
		362, 96,
		344, 74,
		315, 53,
		288, 41,
		258, 36,
		251, 40,
		249, 56,
		252, 66,
		257, 74,
		265, 76,
		275, 72,
		287, 71,
		313, 75,
		328, 81,
		341, 90,
		352, 106,
		364, 127,
		367, 147,
		367, 169,
		363, 197,
		354, 219,
		342, 242,
		326, 262,
		318, 275
	};
	PhysBody* bg12;
	bg12 = App->physics->CreateChain(0, 0, chain_collider13, 60);
	bg12->body->SetType(b2_staticBody);
	bg12->body->GetFixtureList()->SetDensity(0.1f);

	//COLLIDER14
	int chain_collider14[58] = {
		280, 256,
		300, 246,
		307, 235,
		312, 223,
		329, 204,
		339, 184,
		345, 170,
		346, 148,
		344, 127,
		338, 112,
		331, 99,
		321, 93,
		308, 91,
		302, 94,
		304, 105,
		307, 117,
		308, 131,
		305, 147,
		298, 158,
		288, 169,
		273, 176,
		258, 179,
		241, 182,
		223, 194,
		223, 211,
		239, 218,
		253, 224,
		262, 233,
		271, 243
	};
	PhysBody* bg13;
	bg13 = App->physics->CreateChain(0, 0, chain_collider14, 58);
	bg13->body->SetType(b2_staticBody);
	bg13->body->GetFixtureList()->SetDensity(0.1f);

	//COLLIDER15
	int chain_collider15[34] = {
		98, 267,
		102, 247,
		109, 234,
		119, 223,
		139, 213,
		112, 210,
		99, 208,
		77, 200,
		58, 188,
		45, 176,
		44, 182,
		64, 215,
		72, 210,
		82, 210,
		88, 217,
		88, 231,
		90, 257
	};
	PhysBody* bg14;
	bg14 = App->physics->CreateChain(0, 0, chain_collider15, 34);
	bg14->body->SetType(b2_staticBody);
	bg14->body->GetFixtureList()->SetRestitution(1.0f);

	//COLLIDER16
	int chain_collider16[38] = {
		185, 126,
		179, 143,
		171, 159,
		157, 170,
		166, 181,
		174, 186,
		173, 176,
		174, 169,
		181, 161,
		187, 162,
		196, 168,
		199, 175,
		196, 179,
		197, 186,
		206, 178,
		213, 170,
		203, 159,
		194, 146,
		189, 131
	};
	PhysBody* bg15;
	bg15 = App->physics->CreateChain(0, 0, chain_collider16, 38);
	bg15->body->SetType(b2_staticBody);
	bg15->body->GetFixtureList()->SetRestitution(1.0f);

	//COLLIDER17
	int chain_collider17[18] = {
		48, 130,
		55, 146,
		72, 159,
		99, 175,
		99, 182,
		78, 175,
		66, 164,
		46, 143,
		41, 133
	};
	PhysBody* bg16;
	bg16 = App->physics->CreateChain(0, 0, chain_collider17, 18);
	bg16->body->SetType(b2_staticBody);
	bg16->body->GetFixtureList()->SetRestitution(1.0f);

	//COLLIDER18
	int chain_collider18[30] = {
		46, 102,
		52, 87,
		59, 75,
		77, 61,
		93, 50,
		110, 42,
		126, 38,
		124, 33,
		112, 34,
		93, 44,
		76, 54,
		59, 67,
		46, 84,
		43, 93,
		41, 100
	};
	PhysBody* bg17;
	bg17 = App->physics->CreateChain(0, 0, chain_collider18, 30);
	bg17->body->SetType(b2_staticBody);
	bg17->body->GetFixtureList()->SetRestitution(1.0f);

	//COLLIDER19
	int chain_collider19[14] = {
		143, 35,
		144, 49,
		145, 60,
		150, 61,
		151, 51,
		151, 41,
		150, 35
	};
	PhysBody* bg18;
	bg18 = App->physics->CreateChain(0, 0, chain_collider19, 14);
	bg18->body->SetType(b2_staticBody);
	bg18->body->GetFixtureList()->SetDensity(0.1f);

	//COLLIDER20
	int chain_collider20[16] = {
		169, 43,
		169, 54,
		170, 80,
		172, 85,
		176, 82,
		176, 70,
		176, 41,
		172, 38
	};
	PhysBody* bg19;
	bg19 = App->physics->CreateChain(0, 0, chain_collider20, 16);
	bg19->body->SetType(b2_staticBody);
	bg19->body->GetFixtureList()->SetDensity(0.1f);

	//COLLIDER21
	int chain_collider21[12] = {
		197, 41,
		197, 82,
		200, 86,
		205, 83,
		205, 42,
		201, 38
	};
	PhysBody* bg20;
	bg20 = App->physics->CreateChain(0, 0, chain_collider21, 12);
	bg20->body->SetType(b2_staticBody);
	bg20->body->GetFixtureList()->SetDensity(0.1f);

	//COLLIDER22
	int chain_collider22[12] = {
		222, 35,
		222, 60,
		226, 62,
		230, 60,
		230, 35,
		226, 33
	};
	PhysBody* bg21;
	bg21 = App->physics->CreateChain(0, 0, chain_collider22, 12);
	bg21->body->SetType(b2_staticBody);
	bg21->body->GetFixtureList()->SetDensity(0.1f);

	//COLLIDER23
	int chain_collider23[80] = {
		113, 64,
		103, 65,
		93, 70,
		89, 73,
		90, 85,
		85, 88,
		80, 91,
		77, 98,
		69, 101,
		62, 105,
		60, 111,
		62, 118,
		67, 122,
		75, 125,
		86, 123,
		91, 119,
		101, 118,
		103, 123,
		113, 124,
		110, 130,
		109, 137,
		110, 145,
		115, 152,
		123, 155,
		132, 154,
		138, 148,
		139, 139,
		135, 130,
		130, 124,
		127, 119,
		127, 114,
		130, 109,
		136, 107,
		141, 102,
		144, 96,
		144, 87,
		142, 81,
		137, 75,
		128, 67,
		121, 64
	};
	PhysBody* bg22;
	bg22 = App->physics->CreateChain(0, 0, chain_collider23, 80);
	bg22->body->SetType(b2_staticBody);
	bg22->body->GetFixtureList()->SetRestitution(1.0f);

	//COLLIDER24
	int chain_collider24[44] = {
		247, 82,
		241, 85,
		239, 96,
		235, 102,
		229, 109,
		225, 118,
		226, 127,
		229, 135,
		235, 141,
		240, 144,
		248, 145,
		259, 144,
		267, 138,
		271, 131,
		272, 122,
		271, 113,
		266, 107,
		261, 101,
		261, 95,
		260, 89,
		257, 84,
		252, 81
	};
	PhysBody* bg23;
	bg23 = App->physics->CreateChain(0, 0, chain_collider24, 44);
	bg23->body->SetType(b2_staticBody);
	bg23->body->GetFixtureList()->SetRestitution(1.0f);

	//COLLIDER25
	int chain_collider25[8] = {
		159, 247,
		146, 261,
		157, 273,
		171, 261
	};
	PhysBody* bg24;
	bg24 = App->physics->CreateChain(0, 0, chain_collider25, 8);
	bg24->body->SetType(b2_staticBody);
	bg24->body->GetFixtureList()->SetRestitution(0.5f);

	//COLLIDER26
	int chain_collider26[8] = {
		216, 247,
		205, 262,
		218, 275,
		233, 260
	};
	PhysBody* bg25;
	bg25 = App->physics->CreateChain(0, 0, chain_collider26, 8);
	bg25->body->SetType(b2_staticBody);
	bg25->body->GetFixtureList()->SetRestitution(0.5f);

	//COLLIDER PRUEBA SPAWN
	/*int collider_p[12] = {
		378, 581,
		400, 581,
		400, 547,
		377, 547,
		377, 565,
		378, 572
	};
	PhysBody* bgp;
	bgp = App->physics->CreateChain(0, 0, collider_p, 12);
	bgp->body->SetType(b2_staticBody);
	bgp->body->GetFixtureList()->SetDensity(0.1f);*/

	//FLIPPERS
	App->physics->CreateFlipper_l();
	App->physics->CreateFlipper_r();

	//start circle
	circles.add(App->physics->CreateCircle(388, 540, 5));
	circles.getLast()->data->listener = this;

	//spring
	spring = App->physics->CreateRectangle(388, 565, 20, 40);
	//spring->body->SetType(b2_staticBody);

	//stop spring
	int stopspring1[8] = {
		377, 516,
		384, 545,
		377, 545,
		377, 517
	};
	stop1 = App->physics->CreateChain(-5, 0, stopspring1, 8);
	stop1->body->SetType(b2_staticBody);

	int stopspring2[8] = {
		401, 518,
		396, 545,
		402, 545,
		402, 518
	};
	stop2 = App->physics->CreateChain(0, 0, stopspring2, 8);
	stop2->body->SetType(b2_staticBody);

	//sensors
	//Sensors.add(App->physics->CreateRectangleSensor(185, 595, 150, 2));
	respawn_sensor = App->physics->CreateRectangleSensor(185, 595, 150, 2);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//BACKGROUND
	background.x = 0;
	background.y= 0;
	background.h = 599;
	background.w = 598;
	App->renderer->Blit(general, 0, 0, &background);
	
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 5));
		circles.getLast()->data->listener = this;
	}

	//INPUT SPRING
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		spring->body->ApplyForceToCenter(b2Vec2(0.0f, 0.01f), true);
	}
	else
	{
		spring->body->ApplyForceToCenter(b2Vec2(0.0f, -75.0f), true);
	}

	int x, y;
	spring->GetPosition(x, y);
	App->renderer->Blit(spring_text, x, y, NULL, 1.0f);

	//INPUT FLIPPERS
	
	//App->renderer->Blit(flip_l, 132, 557,NULL, 1.0f, RADTODEG *App->physics->ret_flip_l->GetAngle(), -0.5f);

	App->renderer->Blit(flip_l, 135, 550 ,NULL, 1.0f, RADTODEG *App->physics->ret_flip_l->GetAngle(), 0, 0);
	App->renderer->Blit(flip_r, 192, 551, NULL, 1.0f, RADTODEG* App->physics->ret_flip_r->GetAngle(), 48,0);

	if (App->input->GetKey(SDL_SCANCODE_Z) || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		App->physics->ret_flip_l->ApplyTorque(-100.0, true);
	}
	else {
		if (App->physics->ret_flip_l->IsAwake()) {
			App->physics->ret_flip_l->ApplyTorque(150.0, false);
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_M) || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		App->physics->ret_flip_r->ApplyTorque(100.0, true);
	}
	else {
		if (App->physics->ret_flip_r->IsAwake()) {
			App->physics->ret_flip_r->ApplyTorque(-150.0, false);
		}
	}

	//RESPAWN BALL -------------------------------------------------------------
	


	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	/*if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}*/

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}
	/*
	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/


	
	p2List_item<PhysBody*>* sens = Sensors.getFirst();
	
	if (bodyA == respawn_sensor || bodyB == respawn_sensor) {
		App->renderer->Blit(loselife, 500, 233, NULL);
	}
	
}
