#pragma once
#include "Shader.h"

class ColorShader : public Shader 
{
public:
	ColorShader();
	~ColorShader();
	void vert(const VertexInput& in, FragmentInput& out) override;
	bool frag(const FragmentInput& in, Color& out) override;

	void set_model_matrix(Matrix matrix);
	void set_view_matrix(Matrix matrix);
	void set_projection_matrix(Matrix matrix);

private:
	Matrix _model_matrix;
	Matrix _view_matrix;
	Matrix _proj_matrix;
};

