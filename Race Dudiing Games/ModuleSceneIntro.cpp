#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	// Create sensor cube (will trigger with car)
	sensor_cube = App->physics->AddBody(Cube(5, 5, 5), 0.0);
	sensor_cube->SetAsSensor(true);
	sensor_cube->SetPos(0, 3, 0);

	// Frozen area
	frozen_area = App->physics->AddBody(Cube(20, 5, 40), 0.0);
	frozen_area->SetAsSensor(true);
	frozen_area->SetPos(-40, 5, 90);
	frozen_area = App->physics->AddBody(Cube(40, 5, 20), 0.0);
	frozen_area->SetAsSensor(true);
	frozen_area->SetPos(-10, 5, 100);
	frozen_area = App->physics->AddBody(Cube(20, 5, 40), 0.0);
	frozen_area->SetAsSensor(true);
	frozen_area->SetPos(0, 5, 130);
	frozen_area = App->physics->AddBody(Cube(80, 5, 20), 0.0);
	frozen_area->SetAsSensor(true);
	frozen_area->SetPos(-50, 5, 140);

	// Muddy area
	muddy_area = App->physics->AddBody(Cube(20, 5, 80), 0.0);
	muddy_area->SetAsSensor(true);
	muddy_area->SetPos(120, 5, -90);
	muddy_area = App->physics->AddBody(Cube(60, 5, 20), 0.0);
	muddy_area->SetAsSensor(true);
	muddy_area->SetPos(100, 5, -40);
	muddy_area = App->physics->AddBody(Cube(20, 5, 60), 0.0);
	muddy_area->SetAsSensor(true);
	muddy_area->SetPos(60, 5, -20);
	muddy_area = App->physics->AddBody(Cube(60, 5, 20), 0.0);
	muddy_area->SetAsSensor(true);
	muddy_area->SetPos(80, 5, 20);

	//death zone
	death_zone = App->physics->AddBody(Cube(500, 1, 500), 0.0f, true);
	death_zone->SetPos(0, 0, 0);

	//inici
	CreateElement(new Cube(20, 1, 60), vec3(0, 1, 20), 0, vec3(1, 0, 0));
	CreateElement(new Cube(1, 10, 1), vec3(10, 5, 15), 0, vec3(1, 0, 0))->color = Black;
	CreateElement(new Cube(1, 10, 1), vec3(-10, 5, 15), 0, vec3(1, 0, 0))->color = Black;
	CreateElement(new Cube(20, 3, 0.8), vec3(0, 8, 15), 0, vec3(1, 0, 0))->color = Green;
	CreateElement(new Cube(16, 2, 10), vec3(0, 2, 70), -25, vec3(1, 0, 0)); //Rampa

	//primera U
	CreateElement(new Cube(20, 1, 60), vec3(-20, 1, 60), 90, vec3(0, 1, 0));
	CreateElement(new Cube(20, 1, 40), vec3(-40, 1, 90), 0, vec3(0, 1, 0))->color = LightBlue;
	CreateElement(new Cube(20, 1, 40), vec3(-10, 1, 100), 90, vec3(0, 1, 0))->color = LightBlue;

	//primera L
	CreateElement(new Cube(20, 1, 40), vec3(0, 1, 130), 0, vec3(0, 1, 0))->color = LightBlue;
	CreateElement(new Cube(20, 1, 80), vec3(-50, 1, 140), 90, vec3(0, 1, 0))->color = LightBlue;


	//Recta
	CreateElement(new Cube(20, 1, 160), vec3(-100, 1, 70), 0, vec3(1, 0, 0));
	CreateElement(new Cube(10, 10, 1), vec3(-95, 1, 85), 0, vec3(1, 0, 0)); //paret
	CreateElement(new Cube(10, 10, 1), vec3(-105, 1, 70), 0, vec3(1, 0, 0)); //paret
	CreateElement(new Cube(10, 10, 1), vec3(-95, 1, 55), 0, vec3(1, 0, 0)); //paret
	CreateElement(new Cube(10, 10, 1), vec3(-105, 1, 40), 0, vec3(1, 0, 0)); //paret
	CreateElement(new Cube(10, 10, 1), vec3(-95, 1, 25), 0, vec3(1, 0, 0)); //paret

	
	//segona L
	CreateElement(new Cube(20, 1, 80), vec3(-130, 1, -20), 90, vec3(0, 1, 0));
	CreateElement(new Cube(20, 1, 100), vec3(-180, 1, -60), 0, vec3(1, 0, 0));
	CreateElement(new Cube(2, 10, 2), vec3(-180, 1, -60), 0, vec3(1, 0, 0)); //biga
	CreateElement(new Cube(2, 10, 2), vec3(-175, 1, -70), 0, vec3(1, 0, 0)); //biga
	CreateElement(new Cube(2, 10, 2), vec3(-185, 1, -80), 0, vec3(1, 0, 0)); //biga
	CreateElement(new Cube(2, 10, 2), vec3(-185, 1, -50), 0, vec3(1, 0, 0)); //biga
	CreateElement(new Cube(2, 10, 2), vec3(-180, 1, -40), 0, vec3(1, 0, 0)); //biga
	CreateElement(new Cube(2, 10, 2), vec3(-175, 1, -30), 0, vec3(1, 0, 0)); //biga

	//segona Recta
	CreateElement(new Cube(20, 1, 300), vec3(-40, 1, -120), 90, vec3(0, 1, 0));
	CreateElement(new Cube(10, 2, 16), vec3(-40, 2, -120), 25, vec3(0, 0, 1)); //Rampa
	CreateElement(new Cube(10, 2, 16), vec3(40, 2, -120), 25, vec3(0, 0, 1)); //Rampa
	CreateElement(new Cube(10, 2, 16), vec3(-120, 2, -120), 25, vec3(0, 0, 1)); //Rampa

	//tercera L
	CreateElement(new Cube(20, 1, 80), vec3(120, 1, -90), 0, vec3(1, 0, 0))->color = Brown;
	CreateElement(new Cube(20, 1, 60), vec3(100, 1, -40), 90, vec3(0, 1, 0))->color = Brown;

	//quarta L
	CreateElement(new Cube(20, 1, 60), vec3(60, 1, -20), 0, vec3(1, 0, 0))->color = Brown;
	CreateElement(new Cube(20, 1, 60), vec3(80, 1, 20), 90, vec3(0, 1, 0))->color = Brown;


	//Recta Final
	CreateElement(new Cube(20, 1, 120), vec3(100, 1, 90), 0, vec3(1, 0, 0));
	CreateElement(new Cube(20, 2.5, 0.5), vec3(100, 1, 65), 0, vec3(1, 0, 0)); //bot
	CreateElement(new Cube(20, 2.5, 0.5), vec3(100, 1, 70), 0, vec3(1, 0, 0)); //bot
	CreateElement(new Cube(20, 2.5, 0.5), vec3(100, 1, 75), 0, vec3(1, 0, 0)); //bot
	CreateElement(new Cube(20, 2.5, 0.5), vec3(100, 1, 80), 0, vec3(1, 0, 0)); //bot
	CreateElement(new Cube(20, 2.5, 0.5), vec3(100, 1, 85), 0, vec3(1, 0, 0)); //bot
	CreateElement(new Cube(20, 2.5, 0.5), vec3(100, 1, 90), 0, vec3(1, 0, 0)); //bot
	CreateElement(new Cube(20, 2.5, 0.5), vec3(100, 1, 95), 0, vec3(1, 0, 0)); //bot
	CreateElement(new Cube(20, 2.5, 0.5), vec3(100, 1, 100), 0, vec3(1, 0, 0)); //bot
	CreateElement(new Cube(20, 2.5, 0.5), vec3(100, 1, 105), 0, vec3(1, 0, 0)); //bot
	CreateElement(new Cube(20, 2.5, 0.5), vec3(100, 1, 110), 0, vec3(1, 0, 0)); //bot

	//meta
	CreateElement(new Cube(1, 10, 1), vec3(110, 5, 145), 0, vec3(1, 0, 0))->color = Black;
	CreateElement(new Cube(1, 10, 1), vec3(90, 5, 145), 0, vec3(1, 0, 0))->color = Black;
	CreateElement(new Cube(20, 3, 0.8), vec3(100, 8, 145), 0, vec3(1, 0, 0))->color = Red;
	CreateElement(new Cube(40, 1, 30), vec3(100, 1, 165), 0, vec3(1, 0, 0));
	CreateElement(new Cube(10, 10, 1), vec3(115, 1, 150), 0, vec3(1, 0, 0));
	CreateElement(new Cube(10, 10, 1), vec3(85, 1, 150), 0, vec3(1, 0, 0));
	CreateElement(new Cube(40, 10, 1), vec3(100, 1, 180), 0, vec3(1, 0, 0));
	CreateElement(new Cube(1, 10, 30), vec3(120, 1, 165), 0, vec3(1, 0, 0));
	CreateElement(new Cube(1, 10, 30), vec3(80, 1, 165), 0, vec3(1, 0, 0));
	
	//Cadena Esferas 1
	const int SnakeLength = 7;
	const float BallDistance = 0.3f;
	float XPos = 0.0f;
	float YPos = 15.5f;
	float ZPos = 50.0f;
	float Size = 1.0f;
	Sphere* prevSphere = nullptr;
	Sphere* s = nullptr;
	for (int n = 0; n < SnakeLength; n++) {
		vec3 position = vec3(XPos, YPos, ZPos);
		if(prevSphere == nullptr) s = CreateSphere(new Sphere(1.0f), position, 0.0f);
		else s = CreateSphere(new Sphere(1.0f), position, 100.0f);

		if (prevSphere != nullptr) {
			vec3 anchorA = vec3(0.0f, Size, 0.0f);
			vec3 anchorB = vec3(0.0f, -Size, 0.0f);

			App->physics->AddConstraintP2P(*s->phys, *prevSphere->phys, anchorA, anchorB);
		}
		prevSphere = s;

		XPos += Size + BallDistance;
	}

	//Cadena Esferas 2
	XPos = 0.0f;
	YPos = 15.5f;
	ZPos = 40.0f;
	prevSphere = nullptr;
	s = nullptr;
	for (int n = 0; n < SnakeLength; n++) {
		vec3 position = vec3(XPos, YPos, ZPos);
		if (prevSphere == nullptr) s = CreateSphere(new Sphere(1.0f), position, 0.0f);
		else s = CreateSphere(new Sphere(1.0f), position, 100.0f);

		if (prevSphere != nullptr) {
			vec3 anchorA = vec3(0.0f, Size, 0.0f);
			vec3 anchorB = vec3(0.0f, -Size, 0.0f);

			App->physics->AddConstraintP2P(*s->phys, *prevSphere->phys, anchorA, anchorB);
		}
		prevSphere = s;

		XPos -= Size - BallDistance;
	}

	//Cadena Esferas 3
	XPos = 0.0f;
	YPos = 15.5f;
	ZPos = 30.0f;
	prevSphere = nullptr;
	s = nullptr;
	for (int n = 0; n < SnakeLength; n++) {
		vec3 position = vec3(XPos, YPos, ZPos);
		if (prevSphere == nullptr) s = CreateSphere(new Sphere(1.0f), position, 0.0f);
		else s = CreateSphere(new Sphere(1.0f), position, 100.0f);

		if (prevSphere != nullptr) {
			vec3 anchorA = vec3(0.0f, Size, 0.0f);
			vec3 anchorB = vec3(0.0f, -Size, 0.0f);

			App->physics->AddConstraintP2P(*s->phys, *prevSphere->phys, anchorA, anchorB);
		}
		prevSphere = s;

		XPos += Size + BallDistance;
	}

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	for (uint n = 0; n < primitives.Count(); n++)
		primitives[n]->Update();

	for (int i = 0; i < primitives.Count(); i++) {
		(**primitives.At(i)).Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

Cube* ModuleSceneIntro::CreateElement(Cube* forma, vec3 position, float angle, vec3 axis)
{
	PhysBody3D* physBody;

	forma->SetPos(position.x, position.y, position.z);
	physBody = App->physics->AddBody(*forma, 0.0);
	forma->SetRotation(angle, axis);
	physBody->SetTransform(forma->transform.M);

	forma->phys = physBody;


	primitives.PushBack(forma);
	physBodies.PushBack(physBody);


	return forma;
}

Sphere* ModuleSceneIntro::CreateSphere(Sphere* forma, vec3 position, float mass)
{
	PhysBody3D* physBody;

	forma->SetPos(position.x, position.y, position.z);
	physBody = App->physics->AddBody(*forma, mass);

	forma->phys = physBody;


	primitives.PushBack(forma);
	physBodies.PushBack(physBody);


	return forma;
}


