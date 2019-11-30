#include "DisplayObject.h"
#include "Camera.h"

DisplayObject::DisplayObject() : DisplayObject(0, 0)
{
}

DisplayObject::DisplayObject(Mesh* mesh, Shader* shader)
{
	_mesh = mesh;
	_shader = shader;
	_primitive = Primitive_Triangle;
	position = Vector3(0, 0, 0);
	euler = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
}


DisplayObject::~DisplayObject()
{
}

void DisplayObject::set_mesh(Mesh* mesh)
{
	_mesh = mesh;
}

void DisplayObject::set_shader(Shader* shader)
{
	_shader = shader;
}

Mesh* DisplayObject::get_mesh() const
{
	return _mesh;
}

Shader* DisplayObject::get_shader() const
{
	return _shader;
}

void DisplayObject::draw(Graphics* graphics)
{
	if(_mesh != nullptr && _shader != nullptr)
	{
		_mesh->binddata(graphics);
		Matrix model;
		Quaternion rot;
		Quaternion::euler(&rot, euler);
		Matrix::TRS(&model, position, rot, scale);

		_shader->set_model_matrix(model);
		_shader->set_view_matrix(Camera::get_viewmatrix());
		_shader->set_projection_matrix(Camera::get_projmatrix());
		graphics->set_shader(_shader);
		graphics->draw_primitive(_primitive);
	}
}
