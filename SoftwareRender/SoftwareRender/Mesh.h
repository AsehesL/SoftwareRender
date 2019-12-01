#pragma once
#include "Graphics.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void set_vertices(Vector3*, int);
	void set_uvs(Vector2*, int);
	void set_colors(Color*);
	void set_indices(unsigned int*, int);
	int get_vertexcount();
	int get_indexcount();
	Vector3 get_vertex(int);
	Color get_color(int);
	Vector2 get_uv(int, int);
	
	void binddata(Graphics* graphics);

private:
	Vector3* _vertices;
	Color* _colors;
	Vector2* _uv0s;
	Vector2* _uv1s;
	Vector2* _uv2s;
	Vector2* _uv3s;
	unsigned* _indices;
	int _vertexcount;
	int _indexcount;
	
};

