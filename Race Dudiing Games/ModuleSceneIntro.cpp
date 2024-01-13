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

	CreateElement(new Cube(16, 2, 10), vec3(0, 2, 100), -25, vec3(1, 0, 0));

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




