#pragma once
#include "Math.h"
#include "Color.h"

struct VertexInput
{
public:
	Vector3 vertex;
	Color color;
};

struct FragmentInput
{
public:
	Vector3 position;
	Color color;

	static FragmentInput interpolation(const FragmentInput& i0, const FragmentInput& i1, const FragmentInput& i2, float u, float v, float w)
	{
		FragmentInput o;
		o.position = i0.position * w + i1.position * v + i2.position * u;
		o.color = i0.color * w + i1.color * v + i2.color * u;
		return o;
	}

	static FragmentInput interpolation(const FragmentInput& i0, const FragmentInput& i1, float t)
	{
		FragmentInput o;
		o.position = i0.position * (1 - t) + i1.position * t;
		o.color = i0.color * (1 - t) + i1.color * t;
		return o;
	}
};

class Shader
{
public:
	Shader();
	~Shader();
	virtual void vert(const VertexInput& in, FragmentInput& out) = 0;
	virtual Color frag(const FragmentInput& in) = 0;
};

