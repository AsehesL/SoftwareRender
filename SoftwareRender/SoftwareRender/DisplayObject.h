#pragma once
#include "Mesh.h"
#include "Graphics.h"
#include "Shader.h"

class DisplayObject
{
public:
	DisplayObject();
	DisplayObject(Mesh* mesh, Shader* shader);
	~DisplayObject();
	void set_mesh(Mesh*mesh);
	void set_shader(Shader*shader);
	Mesh* get_mesh() const;
	Shader* get_shader() const;
	void draw(Graphics* graphics);

public:
	Vector3 position;
	Vector3 euler;
	Vector3 scale;

private:
	Mesh* _mesh;
	Shader* _shader;
	Primitive _primitive;
};

