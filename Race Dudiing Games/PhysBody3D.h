#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

class btRigidBody;
class Module;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	btRigidBody* GetBody() const;

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetAsSensor(bool is_sensor);

	btRigidBody* body;

private:
	

public:
	btRigidBody* body = nullptr;
	p2List<Module*> collision_listeners;
	bool is_sensor = false;
	int id = 0;
};

#endif // __PhysBody3D_H__