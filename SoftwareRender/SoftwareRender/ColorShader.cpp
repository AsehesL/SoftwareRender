#include "ColorShader.h"



ColorShader::ColorShader()
{
}


ColorShader::~ColorShader()
{
}

void ColorShader::vert(const VertexInput& in, FragmentInput& out)
{
	Vector4 world, view;
	Vector4 local(in.vertex.x, in.vertex.y, in.vertex.z, 1.0);
	//_model_matrix.transform_point(in.vertex, world);
	//_view_matrix.transform_point(world, view);
	//_proj_matrix.transform_point(view, out.position);
	world = _model_matrix * local;
	view = _view_matrix * world;
	out.position = _proj_matrix * view;
	out.color = in.color;
}

bool ColorShader::frag(const FragmentInput& in, Color& out)
{
	out = in.color;
	return true;
}

void ColorShader::set_model_matrix(Matrix matrix)
{
	_model_matrix = matrix;
}

void ColorShader::set_view_matrix(Matrix matrix)
{
	_view_matrix = matrix;
}

void ColorShader::set_projection_matrix(Matrix matrix)
{
	_proj_matrix = matrix;
}
