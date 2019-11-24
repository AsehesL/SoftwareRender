#pragma once
#include "Math.h"

typedef struct Color
{
public:
	Color() : Color(1.0f,1.0f,1.0f,1.0f){}
	Color(const Color& color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	Color(float red, float green, float blue, float alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	Color(float red, float green, float blue) : Color(red, green, blue, 1.0f){}
	float get_grayscale()
	{
		return 0.299f * r + 0.587f * g + 0.114f * b;
	}
	void to_hsv(float& h, float& s, float& v)
	{
		rgb_to_hsv(*this, h, s, v);
	}

	Color operator+(const Color& color) const
	{
		return Color(r + color.r, g + color.g, b + color.b, a + color.a);
	}
	Color operator-(const Color& color) const
	{
		return Color(r - color.r, g - color.g, b - color.b, a - color.a);
	}
	Color operator*(const Color& color) const
	{
		return Color(r * color.r, g * color.g, b * color.b, a * color.a);
	}
	Color operator*(float scale) const
	{
		return Color(r * scale, g * scale, b * scale, a * scale);
	}
	Color operator/(const Color& color) const
	{
		return Color(r / color.r, g / color.g, b / color.b, a / color.a);
	}
	Color operator/(float scale) const
	{
		float is = 1.0f / scale;
		return Color(r * is, g * is, b * is, a * is);
	}

	Color& operator += (const Color& color)
	{
		r = r + color.r;
		g = g + color.g;
		b = b + color.b;
		a = a + color.a;
		return *this;
	}
	Color& operator -= (const Color& color)
	{
		r = r - color.r;
		g = g - color.g;
		b = b - color.b;
		a = a - color.a;
		return *this;
	}
	Color& operator *= (const Color& color)
	{
		r = r * color.r;
		g = g * color.g;
		b = b * color.b;
		a = a * color.a;
		return *this;
	}
	Color& operator *= (float scale)
	{
		r = r * scale;
		g = g * scale;
		b = b * scale;
		a = a * scale;
		return *this;
	}
	Color& operator /= (const Color& color)
	{
		r = r / color.r;
		g = g / color.g;
		b = b / color.b;
		a = a / color.a;
		return *this;
	}
	Color& operator /= (float scale)
	{
		float is = 1.0f / scale;
		r = r * is;
		g = g * is;
		b = b * is;
		a = a * is;
		return *this;
	}

	bool operator==(const Color& color) const
	{
		return IS_FLOAT_EQUAL(r, color.r) && IS_FLOAT_EQUAL(g, color.g) && IS_FLOAT_EQUAL(b, color.b) && IS_FLOAT_EQUAL(a, color.a);
	}
	bool operator!=(const Color& color) const
	{
		return !(IS_FLOAT_EQUAL(r, color.r)) || !(IS_FLOAT_EQUAL(g, color.g)) || !(IS_FLOAT_EQUAL(b, color.b)) || !(IS_FLOAT_EQUAL(a, color.a));
	}
	float operator[](int index) const
	{
		if (index < 0 || index >= 4)
		{
			throw std::exception("无效的索引");
		}
		switch (index)
		{
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		case 3:
			return a;
		default:
			return 0.0f;
		}
	}

	friend Color operator * (float scale, const Color& color)
	{
		return Color(color.r * scale, color.g * scale, color.b * scale, color.a * scale);
	}

	static void lerp(const Color& a, const Color& b, float t, Color& out)
	{
		out = Color(a.r + (b.r - a.r)*t, a.g + (b.g - a.g)*t, a.b + (b.b - a.b)*t, a.a + (b.a - a.a)*t);
	}
	static Color lerp(const Color& a, const Color& b, float t)
	{
		return Color(a.r + (b.r - a.r)*t, a.g + (b.g - a.g)*t, a.b + (b.b - a.b)*t, a.a + (b.a - a.a)*t);
	}
	static void lerp01(const Color& a, const Color& b, float t, Color& out)
	{
		if (t < 0.0f)
			t = 0.0f;
		else if (t > 1.0f)
			t = 1.0f;
		lerp(a, b, t, out);
	}
	static Color lerp01(const Color& a, const Color& b, float t)
	{
		if (t < 0.0f)
			t = 0.0f;
		else if (t > 1.0f)
			t = 1.0f;
		return lerp(a, b, t);
	}
	static Color hsv_to_rgb(float h, float s, float v)
	{
		Color col = Color(1.0f, 1.0f, 1.0f, 1.0f);
		if (IS_FLOAT_EQUAL(s, 0.0f))
		{
			col.r = v;
			col.g = v;
			col.b = v;
		}
		else if (IS_FLOAT_EQUAL(v, 0.0f))
		{
			col.r = 0.0f;
			col.g = 0.0f;
			col.b = 0.0f;
		}
		else
		{
			col.r = 0.0f;
			col.g = 0.0f;
			col.b = 0.0f;
			float num = h * 6.0f;
			int num2 = (int)floor(num);
			float num3 = num - (float)num2;
			float num4 = v * (1.0f - s);
			float num5 = v * (1.0f - s * num3);
			float num6 = v * (1.0f - s * (1.0f - num3));
			switch (num2 + 1)
			{
			case 0:
				col.r = v;
				col.g = num4;
				col.b = num5;
				break;
			case 1:
				col.r = v;
				col.g = num6;
				col.b = num4;
				break;
			case 2:
				col.r = num5;
				col.g = v;
				col.b = num4;
				break;
			case 3:
				col.r = num4;
				col.g = v;
				col.b = num6;
				break;
			case 4:
				col.r = num4;
				col.g = num5;
				col.b = v;
				break;
			case 5:
				col.r = num6;
				col.g = num4;
				col.b = v;
				break;
			case 6:
				col.r = v;
				col.g = num4;
				col.b = num5;
				break;
			case 7:
				col.r = v;
				col.g = num6;
				col.b = num4;
				break;
			}
		}
		return col;
	}
	static void hsv_to_rgb(float h, float s, float v, Color& out)
	{
		out = hsv_to_rgb(h, s, v);
	}
	
	static void rgb_to_hsv(const Color& color, float& h, float& s, float& v)
	{
		if (color.b > color.g && color.b > color.r)
		{
			rgb_to_hsv_internal(4.0f, color.b, color.r, color.g, h, s, v);
		}
		else if (color.g > color.r)
		{
			rgb_to_hsv_internal(2.0f, color.g, color.b, color.r, h, s, v);
		}
		else
		{
			rgb_to_hsv_internal(0.0f, color.r, color.g, color.b, h, s, v);
		}
	}

private:
	static void rgb_to_hsv_internal(float offset, float dominantcolor, float colorone, float colortwo, float& h, float& s, float& v)
	{
		v = dominantcolor;
		if (!IS_FLOAT_EQUAL(v, 0.0f))
		{
			float num;
			if (colorone > colortwo)
			{
				num = colortwo;
			}
			else
			{
				num = colorone;
			}
			float num2 = v - num;
			if (!IS_FLOAT_EQUAL(num2, 0.0f))
			{
				s = num2 / v;
				h = offset + (colorone - colortwo) / num2;
			}
			else
			{
				s = 0.0f;
				h = offset + (colorone - colortwo);
			}
			h /= 6.0f;
			if (h < 0.0f)
			{
				h += 1.0f;
			}
		}
		else
		{
			s = 0.0f;
			h = 0.0f;
		}
	}

public:
	float r, g, b, a;


} Color;

#define COLOR_RED      Color(1.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_GREEN    Color(0.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_BLUE     Color(0.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_WHITE    Color(1.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_BLACK    Color(0.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_YELLOW   Color(1.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_CYAN     Color(0.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_MAGENTA  Color(1.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_GRAY     Color(0.5f, 0.5f, 0.5f, 1.0f)
#define COLOR_CLEAR    Color(0.0f, 0.0f, 0.0f, 0.0f)

const Color col_red = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color col_green = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color col_blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
const Color col_white = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color col_black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color col_yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
const Color col_cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);
const Color col_magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);
const Color col_gray = Color(0.5f, 0.5f, 0.5f, 1.0f);
const Color col_clear = Color(0.0f, 0.0f, 0.0f, 0.0f);