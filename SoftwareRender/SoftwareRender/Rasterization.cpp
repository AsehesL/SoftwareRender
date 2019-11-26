#include "Rasterization.h"

Rasterization::Rasterization()
{
}


Rasterization::~Rasterization()
{
}

void PointRasterization::rasterize(IRasterizable* target, FragmentInput* inputs, int width, int height)
{
	FragmentInput v = inputs[0];
	float iw = 1.0f / v.position.w;
	int screenVx = int((v.position.x * iw + 1) * 0.5f * width);
	int screenVy = int((-v.position.y * iw + 1) * 0.5f * height);

	if (screenVx < 0 || screenVx >= width)
		return;
	if (screenVy < 0 || screenVy >= height)
		return;
	target->rasterize_fragment(screenVx, screenVy, v);
}

void LineRasterization::rasterize(IRasterizable* target, FragmentInput* inputs, int width, int height)
{
	FragmentInput v0 = inputs[0];
	FragmentInput v1 = inputs[1];
	float iw0 = 1.0f / v0.position.w;
	float iw1 = 1.0f / v1.position.w;
	int x0 = int((v0.position.x * iw0 + 1) * 0.5f * width);
	int y0 = int((-v0.position.y * iw0 + 1) * 0.5f * height);
	int x1 = int((v1.position.x * iw1 + 1) * 0.5f * width);
	int y1 = int((-v1.position.y * iw1 + 1) * 0.5f * height);
	int beginx = x0;
	int beginy = y0;
	int endx = x1;
	int endy = y1;

	int dx = endx - beginx;
	if (dx < 0)
		dx = -dx;
	int dy = endy - beginy;
	if (dy < 0)
		dy = -dy;
	int step = ((endy < beginy && endx >= beginx) || (endy >= beginy && endx < beginx)) ? -1 : 1;

	int p, twod, twodm;
	int pv1, pv2, to;

	float t;

	if (dy < dx)
	{
		p = 2 * dy - dx;
		twod = 2 * dy;
		twodm = 2 * (dy - dx);
		if (beginx > endx)
		{
			pv1 = endx;
			pv2 = endy;
			endx = beginx;
		}
		else
		{
			pv1 = beginx;
			pv2 = beginy;
		}
		to = endx;
	}
	else
	{
		p = 2 * dx - dy;
		twod = 2 * dx;
		twodm = 2 * (dx - dy);
		if (beginy > endy)
		{
			pv2 = endx;
			pv1 = endy;
			endy = beginy;
		}
		else
		{
			pv2 = beginx;
			pv1 = beginy;
		}
		to = endy;
	}
	if (dy < dx) {
		get_lineuv(x0, y0, x1, y1, pv1, pv2, t);
		FragmentInput o = FragmentInput::interpolation(v0, v1, t);
		target->rasterize_fragment(pv1, pv2, o);
	}
	else {
		get_lineuv(x0, y0, x1, y1, pv2, pv1, t);
		FragmentInput o = FragmentInput::interpolation(v0, v1, t);
		target->rasterize_fragment(pv2, pv1, o);
	}
	while (pv1 < to)
	{
		pv1++;
		if (p < 0)
			p += twod;
		else
		{
			pv2 += step;
			p += twodm;
		}
		if (dy < dx) {
			get_lineuv(x0, y0, x1, y1, pv1, pv2, t);
			FragmentInput o = FragmentInput::interpolation(v0, v1, t);
			target->rasterize_fragment(pv1, pv2, o);
		}
		else {
			get_lineuv(x0, y0, x1, y1, pv2, pv1, t);
			FragmentInput o = FragmentInput::interpolation(v0, v1, t);
			target->rasterize_fragment(pv2, pv1, o);
		}
	}
}

void LineRasterization::get_lineuv(int x0, int y0, int x1, int y1, int x, int y, float& t)
{
	float dis = sqrtf((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0));
	float dist = sqrtf((x - x0)*(x - x0) + (y - y0)*(y - y0));
	t = dist / dis;
}

void TriangleRasterization::rasterize(IRasterizable* target, FragmentInput* inputs, int width, int height)
{
	FragmentInput v0 = inputs[0];
	FragmentInput v1 = inputs[1];
	FragmentInput v2 = inputs[2];
	float iw0 = 1.0f / v0.position.w;
	float iw1 = 1.0f / v1.position.w;
	float iw2 = 1.0f / v2.position.w;
	int screenV0x = int((v0.position.x * iw0 + 1) * 0.5f * width);
	int screenV0y = int((-v0.position.y * iw0 + 1) * 0.5f * height);
	int screenV1x = int((v1.position.x * iw1 + 1) * 0.5f * width);
	int screenV1y = int((-v1.position.y * iw1 + 1) * 0.5f * height);
	int screenV2x = int((v2.position.x * iw2 + 1) * 0.5f * width);
	int screenV2y = int((-v2.position.y * iw2 + 1) * 0.5f * height);

	int minx = min_i(screenV0x, min_i(screenV1x, screenV2x));
	int miny = min_i(screenV0y, min_i(screenV1y, screenV2y));
	int maxx = max_i(screenV0x, max_i(screenV1x, screenV2x));
	int maxy = max_i(screenV0y, max_i(screenV1y, screenV2y));

	minx = clamp_i(minx, 0, width - 1);
	maxx = clamp_i(maxx, 0, width - 1);
	miny = clamp_i(miny, 0, height - 1);
	maxy = clamp_i(maxy, 0, height - 1);

	for (int i = minx; i <= maxx; i++)
	{
		for (int j = miny; j <= maxy; j++)
		{
			int bias0 = is_edge_topleft(screenV1x, screenV1y, screenV2x, screenV2y) ? 0 : -1;
			int bias1 = is_edge_topleft(screenV2x, screenV2y, screenV0x, screenV0y) ? 0 : -1;
			int bias2 = is_edge_topleft(screenV0x, screenV0y, screenV1x, screenV1y) ? 0 : -1;

			int w0 = edge_equation(screenV1x, screenV1y, screenV2x, screenV2y, i, j) + bias0;
			int w1 = edge_equation(screenV2x, screenV2y, screenV0x, screenV0y, i, j) + bias1;
			int w2 = edge_equation(screenV0x, screenV0y, screenV1x, screenV1y, i, j) + bias2;

			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				float u, v;
				get_uv(screenV0x, screenV0y, screenV1x, screenV1y, screenV2x, screenV2y, i, j, u, v);

				FragmentInput o = FragmentInput::interpolation(v0, v1, v2, u, v, 1.0f - u - v);
				target->rasterize_fragment(i, j, o);
			}
		}
	}
}

int TriangleRasterization::edge_equation(int beginx, int beginy, int endx, int endy, int x, int y)
{
	return (endx - beginx) * (y - beginy) - (endy - beginy) * (x - beginx);
}

bool TriangleRasterization::is_edge_topleft(int x0, int y0, int x1, int y1)
{
	if (y0 == y1 && x0 > x1)
		return true;
	if (y0 > y1)
		return true;
	return false;
}

void TriangleRasterization::get_uv(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y, float& u, float& v)
{
	float v0x = x2 - x0;
	float v0y = y2 - y0;
	float v1x = x1 - x0;
	float v1y = y1 - y0;
	float v2x = x - x0;
	float v2y = y - y0;

	float dot00 = v0x * v0x + v0y * v0y;
	float dot01 = v0x * v1x + v0y * v1y;
	float dot02 = v0x * v2x + v0y * v2y;
	float dot11 = v1x * v1x + v1y * v1y;
	float dot12 = v1x * v2x + v1y * v2y;

	float inverDeno = 1.0f / (dot00 * dot11 - dot01 * dot01);

	u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
	v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
}
