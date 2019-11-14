#pragma once
#include <math.h>
#include <exception>

#define EPSILNON 0.00000001f
#define D_PI 3.1415926535897f          //π
#define RAD_TO_DEG 57.29577951308f    //角度转弧度
#define DEG_TO_RAD 0.01745329252f     //弧度转角度

#define IS_FLOAT_EQUAL(a, b) (a>=b-EPSILNON&&a<=b+EPSILNON)   //浮点数比较

typedef struct Vector2
{
public:
	Vector2() { x = 0, y = 0; }
	Vector2(const Vector2& vector)
	{
		x = vector.x;
		y = vector.y;
	}
	Vector2(const float x, const float y)
	{
		this->x = x;
		this->y = y;
	}

	float magnitude() const
	{
		return sqrtf(x*x + y * y);
	}

	float sq_magnitude() const
	{
		return x * x + y * y;
	}

	void normalize()
	{
		float m = magnitude();
		if (m > 0.0f)
		{
			float im = 1.0 / m;
			x *= im;
			y *= im;
		}
		else
		{
			x = 0.0f;
			y = 0.0f;
		}
	}

	void get_normalized(Vector2& out) const
	{
		out.x = x;
		out.y = y;
		out.normalize();
	}

	void scale(const Vector2& scale)
	{
		x *= scale.x;
		y *= scale.y;
	}

	float& operator[](int index)
	{
		if (index < 0 || index >= 2)
			throw std::exception("无效的索引");
		switch (index)
		{
		case 0:return x;
		case 1:return y;
		}
	}

	bool operator==(const Vector2& vector) const
	{
		return IS_FLOAT_EQUAL(x, vector.x) && IS_FLOAT_EQUAL(y, vector.y);
	}

	bool operator!=(const Vector2& vector) const
	{
		return !IS_FLOAT_EQUAL(x, vector.x) || !IS_FLOAT_EQUAL(y, vector.y);
	}

	Vector2 operator+(const Vector2 & vector) const
	{
		return Vector2(x + vector.x, y + vector.y);
	}

	Vector2 operator-(const Vector2 & vector) const
	{
		return Vector2(x - vector.x, y - vector.y);
	}

	Vector2 operator*(float value) const
	{
		return Vector2(x * value, y * value);
	}

	Vector2 operator/(float value) const
	{
		float inv = 1.0f / value;
		return Vector2(x * inv, y * inv);
	}

	Vector2 & operator+=(const Vector2 & vector)
	{
		x += vector.x;
		y += vector.y;
		return *this;
	}

	Vector2 & operator-=(const Vector2 & vector)
	{
		x -= vector.x;
		y -= vector.y;
		return *this;
	}

	Vector2 & operator*=(float value)
	{
		x *= value;
		y *= value;
		return *this;
	}

	Vector2 & operator/=(float value)
	{
		x /= value;
		y /= value;
		return *this;
	}

	static void lerp(const Vector2 & a, const Vector2 & b, float t, Vector2& out)
	{
		if (t < 0.0f)
			t = 0.0f;
		else if (t > 1.0f)
			t = 1.0f;
		out = Vector2(a.x + (b.x - a.x)*t, a.y + (b.y - a.y)*t);
	}

	static void reflect(const Vector2 & direction, const Vector2 & normal, Vector2& out)
	{
		out = 2.0f * Vector2::dot(normal, direction) * normal - direction;
	}

	static float magnitude(const Vector2 & vector)
	{
		return sqrtf(vector.x*vector.x + vector.y*vector.y);
	}

	static float sq_magnitude(const Vector2 & vector)
	{
		return vector.x*vector.x + vector.y*vector.y;
	}

	static float Angle(const Vector2 & fromvec, const Vector2 & tovec)
	{
		Vector2 fn, tn;
		fromvec.get_normalized(fn);
		tovec.get_normalized(tn);
		float v = Vector2::dot(fn, tn);
		if (v < -1.0f)
			v = -1.0f;
		else if (v > 1.0f)
			v = 1.0f;
		return acosf(v)*57.29578f;
	}

	static float dot(const Vector2 & lhs, const Vector2 & rhs)
	{
		return lhs.x * rhs.x + lhs.y + rhs.y;
	}

	static float distance(const Vector2 & lhs, const Vector2 & rhs)
	{
		return (lhs - rhs).magnitude();
	}

	static void max(const Vector2 & lhs, const Vector2 & rhs, Vector2& out)
	{
		out = Vector2(lhs.x > rhs.x ? lhs.x : rhs.x, lhs.y > rhs.y ? lhs.y : rhs.y);
	}

	static void min(const Vector2 & lhs, const Vector2 & rhs, Vector2& out)
	{
		out = Vector2(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y);
	}

	static void normalize(const Vector2 & vector, Vector2& out)
	{
		vector.get_normalized(out);
	}

	static void Scale(const Vector2 & a, const Vector2 & b, Vector2& out)
	{
		out = Vector2(a.x * b.x, a.y * b.y);
	}

	friend Vector2 operator*(float v, const Vector2 & vector)
	{
		return Vector2(v * vector.x, v * vector.y);
	}

public:
	float x, y;
} Vector2;


typedef struct Vector3{
public:
	Vector3() { x = 0; y = 0; z = 0; }
	Vector3(const Vector3& vector) { x = vector.x; y = vector.y; z = vector.z; }
	Vector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }

	float magnitude() const
	{
		return sqrtf(x*x + y * y + z * z);
	}
	float sq_magnitude() const
	{
		return x * x + y * y + z * z;
	}
	void normalize()
	{
		float m = magnitude();
		if (m > 0.0f)
		{
			float im = 1.0f / m;
			x *= im;
			y *= im;
			z *= im;
		}
		else {
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
	}
	void get_normalized(Vector3& out) const
	{
		out.x = x;
		out.y = y;
		out.z = z;
		out.normalize();
	}
	void scale(const Vector3& scale)
	{
		x *= scale.x;
		y *= scale.y;
		z *= scale.z;
	}
	float& operator [](int index)
	{
		if (index < 0 || index >= 3)
		{
			throw std::exception("无效的索引");
		}
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}
	bool operator ==(const Vector3& vector) const
	{
		return IS_FLOAT_EQUAL(x, vector.x) && IS_FLOAT_EQUAL(y, vector.y) && IS_FLOAT_EQUAL(z, vector.z);
	}
	bool operator !=(const Vector3& vector) const
	{
		return !IS_FLOAT_EQUAL(x, vector.x) || !IS_FLOAT_EQUAL(y, vector.y) || !IS_FLOAT_EQUAL(z, vector.z);
	}
	Vector3 operator +(const Vector3& vector) const
	{
		return Vector3(x + vector.x, y + vector.y, z + vector.z);
	}
	Vector3 operator-(const Vector3& vector) const
	{
		return Vector3(x - vector.x, y - vector.y, z - vector.z);
	}
	Vector3 operator*(float value) const
	{
		return Vector3(x * value, y * value, z * value);
	}
	Vector3 operator/(float value) const
	{
		float iv = 1.0f / value;
		return Vector3(x * iv, y * iv, z * iv);
	}

	friend Vector3 operator * (float v, const Vector3& vector)
	{
		return Vector3(v * vector.x, v * vector.y, v * vector.z);
	}

	Vector3& operator += (const Vector3& vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		return *this;
	}
	Vector3& operator -= (const Vector3& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		return *this;
	}
	Vector3& operator *= (float value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	Vector3& operator /= (float value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	static void lerp(const Vector3& a, const Vector3& b, float t, Vector3& out)
	{
		if (t < 0.0f)
			t = 0.0f;
		else if (t > 1.0f)
			t = 1.0f;
		out = Vector3(a.x + (b.x - a.x)*t, a.y + (b.y - a.y)*t, a.z + (b.z - a.z)*t);
	}
	static void reflect(const Vector3& direction, const Vector3& normal, Vector3& out)
	{
		out = 2.0f * dot(normal, direction)*normal - direction;
	}
	static float angle(const Vector3& fromvec, const Vector3& tovec)
	{
		Vector3 fn, tn;
		fromvec.get_normalized(fn);
		tovec.get_normalized(tn);
		float v = dot(fn, tn);
		if (v < -1.0f)
			v = -1.0f;
		if (v > 1.0f)
			v = 1.0f;
		return acosf(v) * 57.29578f;
	}
	static float dot(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
	}
	static float distance(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 v = lhs - rhs;
		return v.magnitude();
	}
	static void max(const Vector3& lhs, const Vector3& rhs, Vector3& out)
	{
		out = Vector3(lhs.x > rhs.x ? lhs.x : rhs.x, lhs.y > rhs.y ? lhs.y : rhs.y, lhs.z > rhs.z ? lhs.z : rhs.z);
	}
	static void min(const Vector3& lhs, const Vector3& rhs, Vector3& out)
	{
		out = Vector3(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y, lhs.z < rhs.z ? lhs.z : rhs.z);
	}
	static float magnitude(const Vector3& vector)
	{
		return sqrtf(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
	}
	static float sq_magnitude(const Vector3& vector)
	{
		return vector.x*vector.x + vector.y*vector.y + vector.z*vector.z;
	}
	static void normalize(const Vector3& vector, Vector3& out)
	{
		vector.get_normalized(out);
	}
	static void scale(const Vector3& a, const Vector3& b, Vector3& out)
	{
		out = Vector3(a.x*b.x, a.y*b.y, a.z*b.z);
	}
	static void cross(const Vector3& lhs, const Vector3& rhs, Vector3& out)
	{
		out = Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
	}
	static void project(const Vector3& vector, const Vector3& normal, Vector3& out)
	{
		float n = dot(normal, normal);
		out = Vector3();
		if (n >= EPSILNON)
			out = normal * dot(vector, normal) / n;
	}
	static void project_on_plane(const Vector3& vector, const Vector3& planeNormal, Vector3& out)
	{
		Vector3 pj;
		project(vector, planeNormal, pj);
		out = vector - pj;
	}

public:
	float x, y, z;
} Vector3;

