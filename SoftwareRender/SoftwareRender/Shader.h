#pragma once
#include "Math.h"
#include "Color.h"

struct VertexInput
{
public:
	Vector3 vertex;
	Vector2 uv0;
	Vector2 uv1;
	Vector2 uv2;
	Vector2 uv3;
	Color color;
};

struct FragmentInput
{
public:
	Vector4 position;
	Vector2 uv0;
	Vector2 uv1;
	Vector2 uv2;
	Vector2 uv3;
	Color color;

	static FragmentInput interpolation(const FragmentInput& i0, const FragmentInput& i1, const FragmentInput& i2, float u, float v, float w)
	{
		FragmentInput o;
		o.position = i0.position * w + i1.position * v + i2.position * u;
		o.color = i0.color * w + i1.color * v + i2.color * u;
		o.uv0 = i0.uv0 * w + i1.uv0 * v + i2.uv0 * u;
		o.uv1 = i0.uv1 * w + i1.uv1 * v + i2.uv1 * u;
		o.uv2 = i0.uv2 * w + i1.uv2 * v + i2.uv2 * u;
		o.uv3 = i0.uv3 * w + i1.uv3 * v + i2.uv3 * u;
		return o;
	}

	static FragmentInput interpolation(const FragmentInput& i0, const FragmentInput& i1, float t)
	{
		FragmentInput o;
		o.position = i0.position * (1 - t) + i1.position * t;
		o.color = i0.color * (1 - t) + i1.color * t;
		o.uv0 = i0.uv0 * (1 - t) + i1.uv0 * t;
		o.uv1 = i0.uv1 * (1 - t) + i1.uv1 * t;
		o.uv2 = i0.uv2 * (1 - t) + i1.uv2 * t;
		o.uv3 = i0.uv3 * (1 - t) + i1.uv3 * t;
		return o;
	}
};

class Shader
{
public:
	Shader();
	~Shader();
	virtual void vert(const VertexInput& in, FragmentInput& out) = 0;
	virtual bool frag(const FragmentInput& in, Color& out) = 0;

	void set_model_matrix(Matrix matrix);
	void set_view_matrix(Matrix matrix);
	void set_projection_matrix(Matrix matrix);

protected:
	Matrix _model_matrix;
	Matrix _view_matrix;
	Matrix _proj_matrix;
};

