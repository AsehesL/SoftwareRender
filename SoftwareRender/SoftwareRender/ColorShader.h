#pragma once
#include "Shader.h"

class ColorShader : public Shader 
{
public:
	ColorShader();
	~ColorShader();
	void vert(const VertexInput& in, FragmentInput& out) override;
	bool frag(const FragmentInput& in, Color& out) override;
};

