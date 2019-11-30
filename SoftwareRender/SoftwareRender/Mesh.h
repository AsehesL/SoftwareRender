#pragma once
#include "Graphics.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void set_vertices(Vector3*, int);
	void set_colors(Color*);
	void set_indices(unsigned int*, int);
	int get_vertexcount();
	int get_indexcount();
	Vector3 get_vertex(int);
	Color get_color(int);
	
	void binddata(Graphics* graphics);

private:
	Vector3* _vertices;
	Color* _colors;
	unsigned* _indices;
	int _vertexcount;
	int _indexcount;
	
};

