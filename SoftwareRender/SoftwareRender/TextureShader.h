#pragma once
#include "Shader.h"
#include "Texture.h"

class TextureShader : public Shader
{
public:
	TextureShader();
	~TextureShader();

	void vert(const VertexInput& in, FragmentInput& out) override;
	bool frag(const FragmentInput& in, Color& out) override;

	void set_texture(Texture* texture);

private:
	Texture* _texture;
};

