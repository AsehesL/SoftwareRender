#include "Mesh.h"


Mesh::Mesh()
{
	_vertices = 0;
	_colors = 0;
	_uv0s = 0;
	_uv1s = 0;
	_uv2s = 0;
	_uv3s = 0;
	_indices = 0;
	_vertexcount = 0;
	_indexcount = 0;
}

Mesh::~Mesh()
{
	delete[] _vertices;
	delete[] _colors;
	delete[] _uv0s;
	delete[] _uv1s;
	delete[] _uv2s;
	delete[] _uv3s;
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

void Mesh::set_uvs(Vector2* uvs, int channel)
{
	if(channel == 0)
	{
		if (_uv0s != nullptr)
			delete[] _uv0s;
		_uv0s = uvs;
	}
	else if (channel == 1)
	{
		if (_uv1s != nullptr)
			delete[] _uv1s;
		_uv1s = uvs;
	}
	else if (channel == 2)
	{
		if (_uv2s != nullptr)
			delete[] _uv2s;
		_uv2s = uvs;
	}
	else if (channel == 3)
	{
		if (_uv3s != nullptr)
			delete[] _uv3s;
		_uv3s = uvs;
	}
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
	if (_colors == nullptr)
		throw::std::exception("无法访问顶点颜色");
	return _colors[index];
}

Vector2 Mesh::get_uv(int index, int channel)
{
	if (index >= _vertexcount || index < 0)
		throw::std::exception("无效的顶点索引");
	if(channel == 0)
	{
		if (_uv0s == nullptr)
			throw::std::exception("无法访问UV0");
		else
			return _uv0s[index];
	}
	else if(channel == 1)
	{
		if (_uv1s == nullptr)
			throw::std::exception("无法访问UV1");
		else
			return _uv1s[index];
	}
	else if (channel == 2)
	{
		if (_uv2s == nullptr)
			throw::std::exception("无法访问UV2");
		else
			return _uv2s[index];
	}
	else if (channel == 3)
	{
		if (_uv3s == nullptr)
			throw::std::exception("无法访问UV3");
		else
			return _uv3s[index];
	}
	else
	{
		throw::std::exception("无效的UV通道");
	}
}

void Mesh::binddata(Graphics* graphics)
{
	graphics->bind_vertexdata(_vertices, _vertexcount);
	if (_colors != nullptr)
		graphics->bind_colordata(_colors, _vertexcount);
	if (_uv0s != nullptr)
		graphics->bind_texcoorddata(_uv0s, _vertexcount, 0);
	if (_uv1s != nullptr)
		graphics->bind_texcoorddata(_uv1s, _vertexcount, 1);
	if (_uv2s != nullptr)
		graphics->bind_texcoorddata(_uv2s, _vertexcount, 2);
	if (_uv3s != nullptr)
		graphics->bind_texcoorddata(_uv3s, _vertexcount, 3);
	graphics->bind_indexdata(_indices, _indexcount);
}
