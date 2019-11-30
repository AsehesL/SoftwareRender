#include "Mesh.h"


Mesh::Mesh()
{
	_vertices = 0;
	_colors = 0;
	_indices = 0;
	_vertexcount = 0;
	_indexcount = 0;
}

Mesh::~Mesh()
{
	delete[] _vertices;
	delete[] _colors;
	delete[] _indices;
}

void Mesh::set_vertices(Vector3* vertices, int vertexcount)
{
	if (_vertices != nullptr)
		delete[] _vertices;
	_vertices = vertices;
	if (_vertices == nullptr)
		vertexcount = 0;
	_vertexcount = vertexcount;
}

void Mesh::set_colors(Color* colors)
{
	if (_colors != nullptr)
		delete[] _colors;
	_colors = colors;
}

void Mesh::set_indices(unsigned* indices, int indexcount)
{
	if (_indices != nullptr)
		delete[] _indices;
	_indices = indices;
	if (_indices == nullptr)
		indexcount = 0;
	_indexcount = indexcount;
}

int Mesh::get_vertexcount()
{
	return _vertexcount;
}

int Mesh::get_indexcount()
{
	return _indexcount;
}

Vector3 Mesh::get_vertex(int index)
{
	if (index >= _vertexcount || index < 0)
		throw::std::exception("无效的顶点索引");
	return _vertices[index];
}

Color Mesh::get_color(int index)
{
	if (index >= _vertexcount || index < 0)
		throw::std::exception("无效的顶点索引");
	return _colors[index];
}

void Mesh::binddata(Graphics* graphics)
{
	graphics->bind_vertexdata(_vertices, _vertexcount);
	graphics->bind_colordata(_colors, _vertexcount);
	graphics->bind_indexdata(_indices, _indexcount);
}
