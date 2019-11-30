#include "Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::set_model_matrix(Matrix matrix)
{
	_model_matrix = matrix;
}

void Shader::set_view_matrix(Matrix matrix)
{
	_view_matrix = matrix;
}

void Shader::set_projection_matrix(Matrix matrix)
{
	_proj_matrix = matrix;
}
