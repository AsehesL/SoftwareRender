#pragma once
#include "Color.h"
#include "Shader.h"

class IRasterizable
{
public:
	virtual void rasterize_fragment(int x, int y, FragmentInput& frag) = 0;
};

class Rasterization
{
public:
	Rasterization();
	~Rasterization();

	virtual void rasterize(IRasterizable* target, FragmentInput* inputs, int width, int height) = 0;
};

class PointRasterization : public Rasterization
{
public:
	void rasterize(IRasterizable* target, FragmentInput* inputs, int width, int height) override;
};

class LineRasterization : public Rasterization
{
public:
	void rasterize(IRasterizable* target, FragmentInput* inputs, int width, int height) override;

private:
	void get_lineuv(int x0, int y0, int x1, int y1, int x, int y, float& t);
};

class TriangleRasterization : public Rasterization
{
public:
	void rasterize(IRasterizable* target, FragmentInput* inputs, int width, int height) override;

private:
	int edge_equation(int beginx, int beginy, int endx, int endy, int x, int y);
	bool is_edge_topleft(int x0, int y0, int x1, int y1);
	void get_uv(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y, float& u, float &v);
};
