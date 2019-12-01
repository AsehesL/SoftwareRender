#include "TextureShader.h"



TextureShader::TextureShader()
{
}


TextureShader::~TextureShader()
{
}

void TextureShader::vert(const VertexInput& in, FragmentInput& out)
{
	Vector4 world, view;
	Vector4 local(in.vertex.x, in.vertex.y, in.vertex.z, 1.0);
	world = _model_matrix * local;
	view = _view_matrix * world;
	out.position = _proj_matrix * view;
	out.uv0 = in.uv0;
}

bool TextureShader::frag(const FragmentInput& in, Color& out)
{
	out = _texture->sample(in.uv0.x, in.uv0.y);
	if (out.r > 0.5f && out.g > 0.5f && out.b > 0.5f)
		return false;
	return true;
}

void TextureShader::set_texture(Texture* texture)
{
	_texture = texture;
}
