#include "ColorShader.h"



ColorShader::ColorShader()
{
}


ColorShader::~ColorShader()
{
}

void ColorShader::vert(const VertexInput& in, FragmentInput& out)
{
	Vector3 world, view;
	_model_matrix->transform_point(in.vertex, world);
	_view_matrix->transform_point(world, view);
	_proj_matrix->transform_point(view, out.position);
	out.color = in.color;
}

Color ColorShader::frag(const FragmentInput& in)
{
	return in.color;
}

void ColorShader::set_model_matrix(Matrix* matrix)
{
	_model_matrix = matrix;
}

void ColorShader::set_view_matrix(Matrix* matrix)
{
	_view_matrix = matrix;
}

void ColorShader::set_projection_matrix(Matrix* matrix)
{
	_proj_matrix = matrix;
}
