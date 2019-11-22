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
		out = Vector2(a.x + (b.x - a.x)*t, a.y + (b.y - a.y)*t);
	}

	static void lerp01(const Vector2 & a, const Vector2 & b, float t, Vector2& out)
	{
		if (t < 0.0f)
			t = 0.0f;
		else if (t > 1.0f)
			t = 1.0f;
		lerp(a, b, t, out);
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
		out = Vector3(a.x + (b.x - a.x)*t, a.y + (b.y - a.y)*t, a.z + (b.z - a.z)*t);
	}
	static void lerp01(const Vector3& a, const Vector3& b, float t, Vector3& out)
	{
		if (t < 0.0f)
			t = 0.0f;
		else if (t > 1.0f)
			t = 1.0f;
		lerp(a, b, t, out);
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

typedef struct Vector4{
public:
	Vector4() {
		x = 0; y = 0; z = 0; w = 0;
	}
	Vector4(const Vector4& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
		w = vector.w;
	}
	Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	float magnitude() const
	{
		return sqrtf(x*x + y * y + z * z + w * w);
	}
	float sq_magnitude() const
	{
		return x * x + y * y + z * z + w * w;
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
			w *= im;
		}
		else {
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}
	}
	void get_normalized(Vector4& out) const
	{
		out.x = x;
		out.y = y;
		out.z = z;
		out.w = w;
		out.normalize();
	}
	void scale(const Vector4& scale)
	{
		x *= scale.x;
		y *= scale.y;
		z *= scale.z;
		w *= scale.w;
	}
	float& operator [](int index)
	{
		if (index < 0 || index >= 4)
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
		case 3:
			return w;
		}
	}
	bool operator ==(const Vector4& vector) const
	{
		return IS_FLOAT_EQUAL(x, vector.x) && IS_FLOAT_EQUAL(y, vector.y) && IS_FLOAT_EQUAL(z, vector.z) && IS_FLOAT_EQUAL(w, vector.w);
	}
	bool operator !=(const Vector4& vector) const
	{
		return !IS_FLOAT_EQUAL(x, vector.x) || !IS_FLOAT_EQUAL(y, vector.y) || !IS_FLOAT_EQUAL(z, vector.z) || !IS_FLOAT_EQUAL(w, vector.w);
	}
	Vector4 operator +(const Vector4& vector) const
	{
		return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
	}
	Vector4 operator-(const Vector4& vector) const
	{
		return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
	}
	Vector4 operator*(float value) const
	{
		return Vector4(x * value, y * value, z * value, w * value);
	}
	Vector4 operator/(float value) const
	{
		float iv = 1.0f / value;
		return Vector4(x*iv, y*iv, z*iv, w*iv);
	}

	friend Vector4 operator * (float v, const Vector4& vector)
	{
		return Vector4(v * vector.x, v * vector.y, v * vector.z, v * vector.w);
	}

	Vector4& operator += (const Vector4& vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;
		return *this;
	}
	Vector4& operator -= (const Vector4& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;
		return *this;
	}
	Vector4& operator *= (float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}
	Vector4& operator /= (float value)
	{
		float iv = 1.0f / value;
		x *= iv;
		y *= iv;
		z *= iv;
		w *= iv;
		return *this;
	}

	static void lerp(const Vector4& a, const Vector4& b, float t, Vector4& out)
	{
		out = Vector4(a.x + (b.x - a.x)*t, a.y + (b.y - a.y)*t, a.z + (b.z - a.z)*t, a.w + (b.w - a.w)*t);
	}
	static void lerp01(const Vector4& a, const Vector4& b, float t, Vector4& out)
	{
		if (t < 0.0f)
			t = 0.0f;
		else if (t > 1.0f)
			t = 1.0f;
		lerp(a, b, t, out);
	}
	static float dot(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w;
	}
	static float distance(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 v = lhs - rhs;
		return v.magnitude();
	}
	static void max(const Vector4& lhs, const Vector4& rhs, Vector4& out)
	{
		out = Vector4(lhs.x > rhs.x ? lhs.x : rhs.x, lhs.y > rhs.y ? lhs.y : rhs.y, lhs.z > rhs.z ? lhs.z : rhs.z, lhs.w > rhs.w ? lhs.w : rhs.w);
	}
	static void min(const Vector4& lhs, const Vector4& rhs, Vector4& out)
	{
		out = Vector4(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y, lhs.z < rhs.z ? lhs.z : rhs.z, lhs.w < rhs.w ? lhs.w : rhs.w);
	}
	static float magnitude(const Vector4& vector)
	{
		return sqrtf(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z + vector.w*vector.w);
	}
	static float sq_magnitude(const Vector4& vector)
	{
		return vector.x*vector.x + vector.y*vector.y + vector.z*vector.z + vector.w*vector.w;
	}
	static void normalize(const Vector4& vector, Vector4& out)
	{
		vector.get_normalized(out);
	}
	static void scale(const Vector4& a, const Vector4& b, Vector4& out)
	{
		out = Vector4(a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w);
	}
	static void project(const Vector4& a, const Vector4& b, Vector4& out)
	{
		out = b * Vector4::dot(a, b) / Vector4::dot(b, b);
	}

public:
	float x, y, z, w;
} Vector4;

typedef struct Quaternion
{
public:
	Quaternion()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	Quaternion(const Quaternion&quaternion)
	{
		x = quaternion.x;
		y = quaternion.y;
		z = quaternion.z;
		w = quaternion.w;
	}
	Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	void euler(float & eulerX, float & eulerY, float & eulerZ) const
	{
		long sp = -2.0f*(y*z - w * x);

		if (abs(sp) > 0.9999f)
		{
			eulerX = 1.570796f * sp;
			eulerY = atan2f(-x * z + w * y, 0.5f - y * y - z * z);
			eulerZ = 0.0f;
		}
		else
		{
			eulerX = asinf(sp);
			eulerY = atan2f(x*z + w * y, 0.5f - x * x - y * y);
			eulerZ = atan2f(x*y + w * z, 0.5f - x * x - z * z);
		}
		eulerX *= RAD_TO_DEG;
		eulerY *= RAD_TO_DEG;
		eulerZ *= RAD_TO_DEG;
	}
	void euler(Vector3& euler) const
	{
		float sp = -2.0f*(y*z - w * x);

		if (fabsf(sp) > 0.9999f)
		{
			euler.x = 1.570796f * sp;
			euler.y = atan2f(-x * z + w * y, 0.5f - y * y - z * z);
			euler.z = 0.0f;
		}
		else
		{
			euler.x = asinf(sp);
			euler.y = atan2f(x*z + w * y, 0.5f - x * x - y * y);
			euler.z = atan2f(x*y + w * z, 0.5f - x * x - z * z);
		}
		euler.x *= RAD_TO_DEG;
		euler.y *= RAD_TO_DEG;
		euler.z *= RAD_TO_DEG;
	}
	float magnitude() const
	{
		return sqrtf(x*x + y * y + z * z + w * w);
	}

	float& operator [](int index)
	{
		if (index < 0 || index >= 4)
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
		case 3:
			return w;
		default:
			break;
		}
	}
	bool operator ==(const Vector4& quaternion) const
	{
		return IS_FLOAT_EQUAL(x, quaternion.x) && IS_FLOAT_EQUAL(y, quaternion.y) && IS_FLOAT_EQUAL(z, quaternion.z) && IS_FLOAT_EQUAL(w, quaternion.w);
	}
	bool operator !=(const Vector4&quaternion) const
	{
		return !IS_FLOAT_EQUAL(x, quaternion.x) || !IS_FLOAT_EQUAL(y, quaternion.y) || !IS_FLOAT_EQUAL(z, quaternion.z) || !IS_FLOAT_EQUAL(w, quaternion.w);
	}
	Quaternion operator * (const Quaternion& b) const
	{
		Quaternion result;
		result.x = b.w * x + b.x * w + b.z * y - b.y * z;
		result.y = b.w * y + b.y * w + b.x * z - b.z * x;
		result.z = b.w * z + b.z * w + b.y * x - b.x * y;
		result.w = b.w * w - b.x * x - b.y * y - b.z * z;
		return result;
	}
	Quaternion& operator *= (const Quaternion& b)
	{
		Quaternion result;
		result.x = b.w * x + b.x * w + b.z * y - b.y * z;
		result.y = b.w * y + b.y * w + b.x * z - b.z * x;
		result.z = b.w * z + b.z * w + b.y * x - b.x * y;
		result.w = b.w * w - b.x * x - b.y * y - b.z * z;
		return result;
	}

	static void lerp(const Quaternion& a, const Quaternion& b, float t, Quaternion& out)
	{
		float t_ = 1 - t;
		out.x = t_ * a.x + t * b.x;
		out.y = t_ * a.y + t * b.y;
		out.z = t_ * a.z + t * b.z;
		out.w = t_ * a.w + t * b.w;
	}
	static void slerp(const Quaternion& a, const Quaternion& b, float t, Quaternion& out)
	{
		double dot = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;

		Quaternion temp = b;

		if (dot < 0.0f) {
			temp = Quaternion(b.x*-1.0f, b.y*-1.0f, b.z*-1.0f, b.w*-1.0f);
			dot = -dot;
		}

		const float DOT_THRESHOLD = 0.9995;
		if (dot > DOT_THRESHOLD) {

			out = Quaternion(a.x + t * (temp.x - a.x), a.y + t * (temp.y - a.y), a.z + t * (temp.z - a.z), a.w + t * (temp.w - a.w));
			//result.normalize();
			return;
		}

		float theta_0 = acos(dot);
		float theta = theta_0 * t;
		float sin_theta = sin(theta);
		float sin_theta_0 = sin(theta_0);

		float s0 = cos(theta) - dot * sin_theta / sin_theta_0;
		float s1 = sin_theta / sin_theta_0;

		out = Quaternion(s0*a.x + s1 * temp.x, s0*a.y + s1 * temp.y, s0*a.z + s1 * temp.z, s0*a.w + s1 * temp.w);
	}
	static float dot(const Quaternion a, const Quaternion b)
	{
		return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
	}
	static void euler(Quaternion* rotation, float eulerX, float eulerY, float eulerZ)
	{
		float cosx = cosf(eulerX*DEG_TO_RAD*0.5f);
		float cosy = cosf(eulerY*DEG_TO_RAD*0.5f);
		float cosz = cosf(eulerZ*DEG_TO_RAD*0.5f);

		float sinx = sinf(eulerX*DEG_TO_RAD*0.5f);
		float siny = sinf(eulerY*DEG_TO_RAD*0.5f);
		float sinz = sinf(eulerZ*DEG_TO_RAD*0.5f);

		rotation->x = cosy * sinx*cosz + siny * cosx*sinz;
		rotation->y = siny * cosx*cosz - cosy * sinx*sinz;
		rotation->z = cosy * cosx*sinz - siny * sinx*cosz;
		rotation->w = cosy * cosx*cosz + siny * sinx*sinz;
	}
	static void euler(Quaternion* rotation, const Vector3& euler)
	{
		float cosx = cosf(euler.x*DEG_TO_RAD*0.5f);
		float cosy = cosf(euler.y*DEG_TO_RAD*0.5f);
		float cosz = cosf(euler.z*DEG_TO_RAD*0.5f);

		float sinx = sinf(euler.x*DEG_TO_RAD*0.5f);
		float siny = sinf(euler.y*DEG_TO_RAD*0.5f);
		float sinz = sinf(euler.z*DEG_TO_RAD*0.5f);

		rotation->x = cosy * sinx*cosz + siny * cosx*sinz;
		rotation->y = siny * cosx*cosz - cosy * sinx*sinz;
		rotation->z = cosy * cosx*sinz - siny * sinx*cosz;
		rotation->w = cosy * cosx*cosz + siny * sinx*sinz;
	}
	static float magnitude(const Quaternion& quaternion)
	{
		return sqrtf(quaternion.x*quaternion.x + quaternion.y*quaternion.y + quaternion.z*quaternion.z + quaternion.w*quaternion.w);
	}
	static void inverse(const Quaternion& in, Quaternion& out)
	{
		float m = in.magnitude();
		float im = 1.0f / m;
		out.x = -in.x * im;
		out.y = -in.y * im;
		out.z = -in.z * im;
		out.w = in.w * im;
	}

public:
	float x, y, z, w;
} Quaternion;

typedef struct Matrix
{
public:
	Matrix()
	{
		m00 = 0; m01 = 0; m02 = 0; m03 = 0;
		m10 = 0; m11 = 0; m12 = 0; m13 = 0;
		m20 = 0; m21 = 0; m22 = 0; m23 = 0;
		m30 = 0; m31 = 0; m32 = 0; m33 = 0;
	}
	Matrix(const Matrix& matrix)
	{
		m00 = matrix.m00; m01 = matrix.m01; m02 = matrix.m02; m03 = matrix.m03;
		m10 = matrix.m10; m11 = matrix.m11; m12 = matrix.m12; m13 = matrix.m13;
		m20 = matrix.m20; m21 = matrix.m21; m22 = matrix.m22; m23 = matrix.m23;
		m30 = matrix.m30; m31 = matrix.m31; m32 = matrix.m32; m33 = matrix.m33;
	}
	Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
		this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
		this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
		this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
	}
	bool operator == (const Matrix& matrix) const
	{
		if (!IS_FLOAT_EQUAL(m00, matrix.m00))
			return false;
		if (!IS_FLOAT_EQUAL(m01, matrix.m01))
			return false;
		if (!IS_FLOAT_EQUAL(m02, matrix.m02))
			return false;
		if (!IS_FLOAT_EQUAL(m03, matrix.m03))
			return false;
		if (!IS_FLOAT_EQUAL(m10, matrix.m10))
			return false;
		if (!IS_FLOAT_EQUAL(m11, matrix.m11))
			return false;
		if (!IS_FLOAT_EQUAL(m12, matrix.m12))
			return false;
		if (!IS_FLOAT_EQUAL(m13, matrix.m13))
			return false;
		if (!IS_FLOAT_EQUAL(m20, matrix.m20))
			return false;
		if (!IS_FLOAT_EQUAL(m21, matrix.m21))
			return false;
		if (!IS_FLOAT_EQUAL(m22, matrix.m22))
			return false;
		if (!IS_FLOAT_EQUAL(m23, matrix.m23))
			return false;
		if (!IS_FLOAT_EQUAL(m30, matrix.m30))
			return false;
		if (!IS_FLOAT_EQUAL(m31, matrix.m31))
			return false;
		if (!IS_FLOAT_EQUAL(m32, matrix.m32))
			return false;
		if (!IS_FLOAT_EQUAL(m33, matrix.m33))
			return false;
		return true;
	}
	bool operator != (const Matrix& matrix) const
	{
		if (!IS_FLOAT_EQUAL(m00, matrix.m00))
			return true;
		if (!IS_FLOAT_EQUAL(m01, matrix.m01))
			return true;
		if (!IS_FLOAT_EQUAL(m02, matrix.m02))
			return true;
		if (!IS_FLOAT_EQUAL(m03, matrix.m03))
			return true;
		if (!IS_FLOAT_EQUAL(m10, matrix.m10))
			return true;
		if (!IS_FLOAT_EQUAL(m11, matrix.m11))
			return true;
		if (!IS_FLOAT_EQUAL(m12, matrix.m12))
			return true;
		if (!IS_FLOAT_EQUAL(m13, matrix.m13))
			return true;
		if (!IS_FLOAT_EQUAL(m20, matrix.m20))
			return true;
		if (!IS_FLOAT_EQUAL(m21, matrix.m21))
			return true;
		if (!IS_FLOAT_EQUAL(m22, matrix.m22))
			return true;
		if (!IS_FLOAT_EQUAL(m23, matrix.m23))
			return true;
		if (!IS_FLOAT_EQUAL(m30, matrix.m30))
			return true;
		if (!IS_FLOAT_EQUAL(m31, matrix.m31))
			return true;
		if (!IS_FLOAT_EQUAL(m32, matrix.m32))
			return true;
		if (!IS_FLOAT_EQUAL(m33, matrix.m33))
			return true;
		return false;
	}
	Matrix operator * (const Matrix& matrix) const
	{
		float rm00 = m00 * matrix.m00 + m01 * matrix.m10 + m02 * matrix.m20 + m03 * matrix.m30;
		float rm01 = m00 * matrix.m01 + m01 * matrix.m11 + m02 * matrix.m21 + m03 * matrix.m31;
		float rm02 = m00 * matrix.m02 + m01 * matrix.m12 + m02 * matrix.m22 + m03 * matrix.m32;
		float rm03 = m00 * matrix.m03 + m01 * matrix.m13 + m02 * matrix.m23 + m03 * matrix.m33;

		float rm10 = m10 * matrix.m00 + m11 * matrix.m10 + m12 * matrix.m20 + m13 * matrix.m30;
		float rm11 = m10 * matrix.m01 + m11 * matrix.m11 + m12 * matrix.m21 + m13 * matrix.m31;
		float rm12 = m10 * matrix.m02 + m11 * matrix.m12 + m12 * matrix.m22 + m13 * matrix.m32;
		float rm13 = m10 * matrix.m03 + m11 * matrix.m13 + m12 * matrix.m23 + m13 * matrix.m33;

		float rm20 = m20 * matrix.m00 + m21 * matrix.m10 + m22 * matrix.m20 + m23 * matrix.m30;
		float rm21 = m20 * matrix.m01 + m21 * matrix.m11 + m22 * matrix.m21 + m23 * matrix.m31;
		float rm22 = m20 * matrix.m02 + m21 * matrix.m12 + m22 * matrix.m22 + m23 * matrix.m32;
		float rm23 = m20 * matrix.m03 + m21 * matrix.m13 + m22 * matrix.m23 + m23 * matrix.m33;

		float rm30 = m30 * matrix.m00 + m31 * matrix.m10 + m32 * matrix.m20 + m33 * matrix.m30;
		float rm31 = m30 * matrix.m01 + m31 * matrix.m11 + m32 * matrix.m21 + m33 * matrix.m31;
		float rm32 = m30 * matrix.m02 + m31 * matrix.m12 + m32 * matrix.m22 + m33 * matrix.m32;
		float rm33 = m30 * matrix.m03 + m31 * matrix.m13 + m32 * matrix.m23 + m33 * matrix.m33;

		return Matrix(rm00, rm01, rm02, rm03,
			rm10, rm11, rm12, rm13,
			rm20, rm21, rm22, rm23,
			rm30, rm31, rm32, rm33);
	}
	Matrix& operator *= (const Matrix& matrix)
	{
		float rm00 = m00 * matrix.m00 + m01 * matrix.m10 + m02 * matrix.m20 + m03 * matrix.m30;
		float rm01 = m00 * matrix.m01 + m01 * matrix.m11 + m02 * matrix.m21 + m03 * matrix.m31;
		float rm02 = m00 * matrix.m02 + m01 * matrix.m12 + m02 * matrix.m22 + m03 * matrix.m32;
		float rm03 = m00 * matrix.m03 + m01 * matrix.m13 + m02 * matrix.m23 + m03 * matrix.m33;

		float rm10 = m10 * matrix.m00 + m11 * matrix.m10 + m12 * matrix.m20 + m13 * matrix.m30;
		float rm11 = m10 * matrix.m01 + m11 * matrix.m11 + m12 * matrix.m21 + m13 * matrix.m31;
		float rm12 = m10 * matrix.m02 + m11 * matrix.m12 + m12 * matrix.m22 + m13 * matrix.m32;
		float rm13 = m10 * matrix.m03 + m11 * matrix.m13 + m12 * matrix.m23 + m13 * matrix.m33;

		float rm20 = m20 * matrix.m00 + m21 * matrix.m10 + m22 * matrix.m20 + m23 * matrix.m30;
		float rm21 = m20 * matrix.m01 + m21 * matrix.m11 + m22 * matrix.m21 + m23 * matrix.m31;
		float rm22 = m20 * matrix.m02 + m21 * matrix.m12 + m22 * matrix.m22 + m23 * matrix.m32;
		float rm23 = m20 * matrix.m03 + m21 * matrix.m13 + m22 * matrix.m23 + m23 * matrix.m33;

		float rm30 = m30 * matrix.m00 + m31 * matrix.m10 + m32 * matrix.m20 + m33 * matrix.m30;
		float rm31 = m30 * matrix.m01 + m31 * matrix.m11 + m32 * matrix.m21 + m33 * matrix.m31;
		float rm32 = m30 * matrix.m02 + m31 * matrix.m12 + m32 * matrix.m22 + m33 * matrix.m32;
		float rm33 = m30 * matrix.m03 + m31 * matrix.m13 + m32 * matrix.m23 + m33 * matrix.m33;

		m00 = rm00;
		m01 = rm01;
		m02 = rm02;
		m03 = rm03;
		m10 = rm10;
		m11 = rm11;
		m12 = rm12;
		m13 = rm13;
		m20 = rm20;
		m21 = rm21;
		m22 = rm22;
		m23 = rm23;
		m30 = rm30;
		m31 = rm31;
		m32 = rm32;
		m33 = rm33;
		return *this;
	}
	float& operator [](int index)
	{
		if (index < 0 || index >= 16)
		{
			throw std::exception("无效的索引");
		}
		switch (index)
		{
		case 0:
			return m00;
		case 1:
			return m01;
		case 2:
			return m02;
		case 3:
			return m03;
		case 4:
			return m10;
		case 5:
			return m11;
		case 6:
			return m12;
		case 7:
			return m13;
		case 8:
			return m20;
		case 9:
			return m21;
		case 10:
			return m22;
		case 11:
			return m23;
		case 12:
			return m30;
		case 13:
			return m31;
		case 14:
			return m32;
		case 15:
			return m33;
		}
	}
	friend Vector4 operator*(const Vector4& vector, const Matrix& matrix)
	{
		return Vector4(vector.x *matrix.m00 + vector.y *matrix.m10 + vector.z * matrix.m20 + vector.w*matrix.m30,
			vector.x *matrix.m01 + vector.y * matrix.m11 + vector.z *matrix.m21 + vector.w*matrix.m31,
			vector.x *matrix.m02 + vector.y *matrix.m12 + vector.z *matrix.m22 + vector.w*matrix.m32,
			vector.x *matrix.m03 + vector.y * matrix.m13 + vector.z *matrix.m23 + vector.w*matrix.m33);
	}

	void transform_vector(const Vector3& vector, Vector3& out) const
	{
		float x = vector.x * m00 + vector.y * m10 + vector.z * m20;
		float y = vector.x * m01 + vector.y * m11 + vector.z * m21;
		float z = vector.x * m02 + vector.y * m12 + vector.z * m22;

		out.x = x;
		out.y = y;
		out.z = z;
	}
	void transform_point(const Vector3& vector, Vector3& out) const
	{
		float x = vector.x * m00 + vector.y * m10 + vector.z * m20 + m30;
		float y = vector.x * m01 + vector.y * m11 + vector.z * m21 + m31;
		float z = vector.x * m02 + vector.y * m12 + vector.z * m22 + m32;
		float w = vector.x * m03 + vector.y * m13 + vector.z * m23 + m33;

		if (IS_FLOAT_EQUAL(w, 0.0f)) {
			out.x = NAN;
			out.y = NAN;
			out.z = NAN;
			return;
		}
		float iw = 1.0f / w;
		out.x = x * iw;
		out.y = y * iw;
		out.z = z * iw;
	}
	void get_transpose(Matrix& matrix) const
	{
		matrix.m00 = m00;
		matrix.m01 = m10;
		matrix.m02 = m20;
		matrix.m03 = m30;

		matrix.m10 = m01;
		matrix.m11 = m11;
		matrix.m12 = m21;
		matrix.m13 = m31;

		matrix.m20 = m02;
		matrix.m21 = m12;
		matrix.m22 = m22;
		matrix.m23 = m32;

		matrix.m30 = m03;
		matrix.m31 = m13;
		matrix.m32 = m23;
		matrix.m33 = m33;
	}
	void transpose()
	{
		float t01 = m01;
		m01 = m10;
		m10 = t01;

		float t02 = m02;
		m02 = m20;
		m20 = t02;

		float t03 = m03;
		m03 = m30;
		m30 = t03;

		float t12 = m12;
		m12 = m21;
		m21 = t12;

		float t13 = m13;
		m13 = m31;
		m31 = t13;

		float t23 = m23;
		m23 = m32;
		m32 = t23;
	}
	void inverse()
	{
		Matrix tmp;

		tmp[0] = m11 * m22 * m33 -
			m11 * m23 * m32 -
			m21 * m12 * m33 +
			m21 * m13 * m32 +
			m31 * m12 * m23 -
			m31 * m13 * m22;

		tmp[4] = -m10 * m22 * m33 +
			m10 * m23 * m32 +
			m20 * m12 * m33 -
			m20 * m13 * m32 -
			m30 * m12 * m23 +
			m30 * m13 * m22;

		tmp[8] = m10 * m21 * m33 -
			m10 * m23 * m31 -
			m20 * m11 * m33 +
			m20 * m13 * m31 +
			m30 * m11 * m23 -
			m30 * m13 * m21;

		tmp[12] = -m10 * m21 * m32 +
			m10 * m22 * m31 +
			m20 * m11 * m32 -
			m20 * m12 * m31 -
			m30 * m11 * m22 +
			m30 * m12 * m21;

		tmp[1] = -m01 * m22 * m33 +
			m01 * m23 * m32 +
			m21 * m02 * m33 -
			m21 * m03 * m32 -
			m31 * m02 * m23 +
			m31 * m03 * m22;

		tmp[5] = m00 * m22 * m33 -
			m00 * m23 * m32 -
			m20 * m02 * m33 +
			m20 * m03 * m32 +
			m30 * m02 * m23 -
			m30 * m03 * m22;

		tmp[9] = -m00 * m21 * m33 +
			m00 * m23 * m31 +
			m20 * m01 * m33 -
			m20 * m03 * m31 -
			m30 * m01 * m23 +
			m30 * m03 * m21;

		tmp[13] = m00 * m21 * m32 -
			m00 * m22 * m31 -
			m20 * m01 * m32 +
			m20 * m02 * m31 +
			m30 * m01 * m22 -
			m30 * m02 * m21;

		tmp[2] = m01 * m12 * m33 -
			m01 * m13 * m32 -
			m11 * m02 * m33 +
			m11 * m03 * m32 +
			m31 * m02 * m13 -
			m31 * m03 * m12;

		tmp[6] = -m00 * m12 * m33 +
			m00 * m13 * m32 +
			m10 * m02 * m33 -
			m10 * m03 * m32 -
			m30 * m02 * m13 +
			m30 * m03 * m12;

		tmp[10] = m00 * m11 * m33 -
			m00 * m13 * m31 -
			m10 * m01 * m33 +
			m10 * m03 * m31 +
			m30 * m01 * m13 -
			m30 * m03 * m11;

		tmp[14] = -m00 * m11 * m32 +
			m00 * m12 * m31 +
			m10 * m01 * m32 -
			m10 * m02 * m31 -
			m30 * m01 * m12 +
			m30 * m02 * m11;

		tmp[3] = -m01 * m12 * m23 +
			m01 * m13 * m22 +
			m11 * m02 * m23 -
			m11 * m03 * m22 -
			m21 * m02 * m13 +
			m21 * m03 * m12;

		tmp[7] = m00 * m12 * m23 -
			m00 * m13 * m22 -
			m10 * m02 * m23 +
			m10 * m03 * m22 +
			m20 * m02 * m13 -
			m20 * m03 * m12;

		tmp[11] = -m00 * m11 * m23 +
			m00 * m13 * m21 +
			m10 * m01 * m23 -
			m10 * m03 * m21 -
			m20 * m01 * m13 +
			m20 * m03 * m11;

		tmp[15] = m00 * m11 * m22 -
			m00 * m12 * m21 -
			m10 * m01 * m22 +
			m10 * m02 * m21 +
			m20 * m01 * m12 -
			m20 * m02 * m11;

		float det = m00 * tmp[0] + m01 * tmp[4] + m02 * tmp[8] + m03 * tmp[12];

		if (det == 0)
			throw std::exception("不可逆矩阵");

		det = 1.0f / det;

		for (int i = 0; i < 16; i++)
			this->operator[](i) = tmp[i] * det;
	}

	static void perspective(Matrix* matrix, float fov, float aspect, float near, float far)
	{
		float cotfov = 1.0f / tanf(fov*0.5f);
		float delta = far - near;

		matrix->m00 = cotfov / aspect;
		matrix->m01 = 0.0f;
		matrix->m02 = 0.0f;
		matrix->m03 = 0.0f;

		matrix->m10 = 0.0f;
		matrix->m11 = cotfov;
		matrix->m12 = 0.0f;
		matrix->m13 = 0.0f;

		matrix->m20 = 0.0f;
		matrix->m21 = 0.0f;
		matrix->m22 = -(far + near) / delta;
		matrix->m23 = -1.0f;

		matrix->m30 = 0.0f;
		matrix->m31 = 0.0f;
		matrix->m32 = -2.0f*near*far / delta;
		matrix->m33 = 0.0f;
	}
	static void ortho(Matrix* matrix, float width, float height, float near, float far)
	{
		float fn = 1.0f / (far - near);
		matrix->m00 = 2.0f / width;
		matrix->m01 = 0.0f;
		matrix->m02 = 0.0f;
		matrix->m03 = 0.0f;
		matrix->m10 = 0.0f;
		matrix->m11 = 2.0f / height;
		matrix->m12 = 0.0f;
		matrix->m13 = 0.0f;
		matrix->m20 = 0.0f;
		matrix->m21 = 0.0f;
		matrix->m22 = -2.0*fn;
		matrix->m23 = 0.0f;
		matrix->m30 = 0.0f;
		matrix->m31 = 0.0f;
		matrix->m32 = -(far + near)*fn;
		matrix->m33 = 1.0f;
	}
	static void identity(Matrix*matrix)
	{
		matrix->m00 = 1;
		matrix->m01 = 0;
		matrix->m02 = 0;
		matrix->m03 = 0;
		matrix->m10 = 0;
		matrix->m11 = 1;
		matrix->m12 = 0;
		matrix->m13 = 0;
		matrix->m20 = 0;
		matrix->m21 = 0;
		matrix->m22 = 1;
		matrix->m23 = 0;
		matrix->m30 = 0;
		matrix->m31 = 0;
		matrix->m32 = 0;
		matrix->m33 = 1;
	}
	static void scale(Matrix*matrix, float x, float y, float z)
	{
		matrix->m00 = x;
		matrix->m01 = 0;
		matrix->m02 = 0;
		matrix->m03 = 0;

		matrix->m10 = 0;
		matrix->m11 = y;
		matrix->m12 = 0;
		matrix->m13 = 0;

		matrix->m20 = 0;
		matrix->m21 = 0;
		matrix->m22 = z;
		matrix->m23 = 0;

		matrix->m30 = 0;
		matrix->m31 = 0;
		matrix->m32 = 0;
		matrix->m33 = 1;
	}
	static void translate(Matrix*matrix, float x, float y, float z)
	{
		matrix->m00 = 1;
		matrix->m01 = 0;
		matrix->m02 = 0;
		matrix->m03 = 0;

		matrix->m10 = 0;
		matrix->m11 = 1;
		matrix->m12 = 0;
		matrix->m13 = 0;

		matrix->m20 = 0;
		matrix->m21 = 0;
		matrix->m22 = 1;
		matrix->m23 = 0;

		matrix->m30 = x;
		matrix->m31 = y;
		matrix->m32 = z;
		matrix->m33 = 1;
	}
	static void rotate_x(Matrix* matrix, float angle)
	{
		float cosag = cosf(angle);
		float sinag = sinf(angle);
		matrix->m00 = 1.0f;
		matrix->m01 = 0.0f;
		matrix->m02 = 0.0f;
		matrix->m03 = 0.0f;
		matrix->m10 = 0.0f;
		matrix->m11 = cosag;
		matrix->m12 = sinag;
		matrix->m13 = 0.0f;
		matrix->m20 = 0.0f;
		matrix->m21 = -sinag;
		matrix->m22 = cosag;
		matrix->m23 = 0.0f;
		matrix->m30 = 0.0f;
		matrix->m31 = 0.0f;
		matrix->m32 = 0.0f;
		matrix->m33 = 1.0f;
	}
	static void rotate_y(Matrix* matrix, float angle)
	{
		float cosag = cosf(angle);
		float sinag = sinf(angle);
		matrix->m00 = cosag;
		matrix->m01 = 0.0f;
		matrix->m02 = -sinag;
		matrix->m03 = 0.0f;
		matrix->m10 = 0.0f;
		matrix->m11 = 1.0f;
		matrix->m12 = 0.0f;
		matrix->m13 = 0.0f;
		matrix->m20 = sinag;
		matrix->m21 = 0.0f;
		matrix->m22 = cosag;
		matrix->m23 = 0.0f;
		matrix->m30 = 0.0f;
		matrix->m31 = 0.0f;
		matrix->m32 = 0.0f;
		matrix->m33 = 1.0f;
	}
	static void rotate_z(Matrix* matrix, float angle)
	{
		float cosag = cosf(angle);
		float sinag = sinf(angle);
		matrix->m00 = cosag;
		matrix->m01 = sinag;
		matrix->m02 = 0.0f;
		matrix->m03 = 0.0f;
		matrix->m10 = -sinag;
		matrix->m11 = cosag;
		matrix->m12 = 0.0f;
		matrix->m13 = 0.0f;
		matrix->m20 = 0.0f;
		matrix->m21 = 0.0f;
		matrix->m22 = 1.0f;
		matrix->m23 = 0.0f;
		matrix->m30 = 0.0f;
		matrix->m31 = 0.0f;
		matrix->m32 = 0.0f;
		matrix->m33 = 1.0f;
	}
	static void rotate(Matrix* matrix, const Quaternion& rotation)
	{
		float x2 = 2.0f*rotation.x*rotation.x;
		float y2 = 2.0f*rotation.y*rotation.y;
		float z2 = 2.0f*rotation.z*rotation.z;
		float xy = 2.0f*rotation.x*rotation.y;
		float xz = 2.0f*rotation.x*rotation.z;
		float xw = 2.0f*rotation.x*rotation.w;
		float yz = 2.0f*rotation.y*rotation.z;
		float yw = 2.0f*rotation.y*rotation.w;
		float zw = 2.0f*rotation.z*rotation.w;
		matrix->m00 = 1.0f - y2 - z2;
		matrix->m01 = xy + zw;
		matrix->m02 = xz - yw;
		matrix->m03 = 0.0f;
		matrix->m10 = xy - zw;
		matrix->m11 = 1.0f - x2 - z2;
		matrix->m12 = yz + xw;
		matrix->m13 = 0.0f;
		matrix->m20 = xz + yw;
		matrix->m21 = yz - xw;
		matrix->m22 = 1.0f - x2 - y2;
		matrix->m23 = 0.0f;
		matrix->m30 = 0.0f;
		matrix->m31 = 0.0f;
		matrix->m32 = 0.0f;
		matrix->m33 = 1.0f;
	}
	static void TRS(Matrix*matrix, const Vector3&position, const Quaternion&rotation, const Vector3&scale)
	{
		float x2 = 2.0f*rotation.x*rotation.x;
		float y2 = 2.0f*rotation.y*rotation.y;
		float z2 = 2.0f*rotation.z*rotation.z;
		float xy = 2.0f*rotation.x*rotation.y;
		float xz = 2.0f*rotation.x*rotation.z;
		float xw = 2.0f*rotation.x*rotation.w;
		float yz = 2.0f*rotation.y*rotation.z;
		float yw = 2.0f*rotation.y*rotation.w;
		float zw = 2.0f*rotation.z*rotation.w;
		float ra = 1.0f - y2 - z2;
		float rb = xy + zw;
		float rc = xz - yw;
		float rd = xy - zw;
		float re = 1.0f - x2 - z2;
		float rf = yz + xw;
		float rg = xz + yw;
		float rh = yz - xw;
		float ri = 1.0f - x2 - y2;

		matrix->m00 = scale.x*ra;
		matrix->m01 = scale.x*rb;
		matrix->m02 = scale.x*rc;
		matrix->m03 = 0.0f;
		matrix->m10 = scale.y*rd;
		matrix->m11 = scale.y*re;
		matrix->m12 = scale.y*rf;
		matrix->m13 = 0.0f;
		matrix->m20 = scale.z*rg;
		matrix->m21 = scale.z*rh;
		matrix->m22 = scale.z*ri;
		matrix->m23 = 0.0f;
		matrix->m30 = position.x;
		matrix->m31 = position.y;
		matrix->m32 = position.z;
		matrix->m33 = 1.0f;
	}
	//static void TRS(DMatrix4x4*, DVector3* right, DVector3* up, DVector3* forward, const DVector3&, const DQuaterion&, const DVector3&);
	static void lookat(Matrix* matrix, const Vector3& eye, const Vector3& lookat, const Vector3& up)
	{
		Vector3 x, y, z;
		(lookat - eye).get_normalized(z);
		Vector3::cross(up, z, x);
		x.normalize();
		Vector3::cross(z, x, y);

		matrix->m00 = x.x;
		matrix->m10 = x.y;
		matrix->m20 = x.z;

		matrix->m01 = y.x;
		matrix->m11 = y.y;
		matrix->m21 = y.z;

		matrix->m02 = -z.x;
		matrix->m12 = -z.y;
		matrix->m22 = -z.z;

		matrix->m30 = -Vector3::dot(x, eye);
		matrix->m31 = -Vector3::dot(y, eye);
		matrix->m32 = Vector3::dot(z, eye);

		matrix->m03 = 0.0f;
		matrix->m13 = 0.0f;
		matrix->m23 = 0.0f;
		matrix->m33 = 1.0f;
	}
	static void transpose(Matrix* out, const Matrix& target)
	{
		out->m00 = target.m00;
		out->m11 = target.m11;
		out->m22 = target.m22;
		out->m33 = target.m33;

		float t01, t02, t03, t10, t12, t13, t20, t21, t23, t30, t31, t32;
		t01 = target.m01;
		t02 = target.m02;
		t03 = target.m03;
		t10 = target.m10;
		t12 = target.m12;
		t13 = target.m13;
		t20 = target.m20;
		t21 = target.m21;
		t23 = target.m23;
		t30 = target.m30;
		t31 = target.m31;
		t32 = target.m32;

		out->m01 = t10;
		out->m02 = t20;
		out->m03 = t30;

		out->m10 = t01;
		out->m12 = t21;
		out->m13 = t31;

		out->m20 = t02;
		out->m21 = t12;
		out->m23 = t32;

		out->m30 = t03;
		out->m31 = t13;
		out->m32 = t23;
	}
	static void inverse(Matrix* out, const Matrix& target)
	{
		Matrix tmp;

		tmp[0] = target.m11 * target.m22 * target.m33 -
			target.m11 * target.m23 * target.m32 -
			target.m21 * target.m12 * target.m33 +
			target.m21 * target.m13 * target.m32 +
			target.m31 * target.m12 * target.m23 -
			target.m31 * target.m13 * target.m22;

		tmp[4] = -target.m10 * target.m22 * target.m33 +
			target.m10 * target.m23 * target.m32 +
			target.m20 * target.m12 * target.m33 -
			target.m20 * target.m13 * target.m32 -
			target.m30 * target.m12 * target.m23 +
			target.m30 * target.m13 * target.m22;

		tmp[8] = target.m10 * target.m21 * target.m33 -
			target.m10 * target.m23 * target.m31 -
			target.m20 * target.m11 * target.m33 +
			target.m20 * target.m13 * target.m31 +
			target.m30 * target.m11 * target.m23 -
			target.m30 * target.m13 * target.m21;

		tmp[12] = -target.m10 * target.m21 * target.m32 +
			target.m10 * target.m22 * target.m31 +
			target.m20 * target.m11 * target.m32 -
			target.m20 * target.m12 * target.m31 -
			target.m30 * target.m11 * target.m22 +
			target.m30 * target.m12 * target.m21;

		tmp[1] = -target.m01 * target.m22 * target.m33 +
			target.m01 * target.m23 * target.m32 +
			target.m21 * target.m02 * target.m33 -
			target.m21 * target.m03 * target.m32 -
			target.m31 * target.m02 * target.m23 +
			target.m31 * target.m03 * target.m22;

		tmp[5] = target.m00 * target.m22 * target.m33 -
			target.m00 * target.m23 * target.m32 -
			target.m20 * target.m02 * target.m33 +
			target.m20 * target.m03 * target.m32 +
			target.m30 * target.m02 * target.m23 -
			target.m30 * target.m03 * target.m22;

		tmp[9] = -target.m00 * target.m21 * target.m33 +
			target.m00 * target.m23 * target.m31 +
			target.m20 * target.m01 * target.m33 -
			target.m20 * target.m03 * target.m31 -
			target.m30 * target.m01 * target.m23 +
			target.m30 * target.m03 * target.m21;

		tmp[13] = target.m00 * target.m21 * target.m32 -
			target.m00 * target.m22 * target.m31 -
			target.m20 * target.m01 * target.m32 +
			target.m20 * target.m02 * target.m31 +
			target.m30 * target.m01 * target.m22 -
			target.m30 * target.m02 * target.m21;

		tmp[2] = target.m01 * target.m12 * target.m33 -
			target.m01 * target.m13 * target.m32 -
			target.m11 * target.m02 * target.m33 +
			target.m11 * target.m03 * target.m32 +
			target.m31 * target.m02 * target.m13 -
			target.m31 * target.m03 * target.m12;

		tmp[6] = -target.m00 * target.m12 * target.m33 +
			target.m00 * target.m13 * target.m32 +
			target.m10 * target.m02 * target.m33 -
			target.m10 * target.m03 * target.m32 -
			target.m30 * target.m02 * target.m13 +
			target.m30 * target.m03 * target.m12;

		tmp[10] = target.m00 * target.m11 * target.m33 -
			target.m00 * target.m13 * target.m31 -
			target.m10 * target.m01 * target.m33 +
			target.m10 * target.m03 * target.m31 +
			target.m30 * target.m01 * target.m13 -
			target.m30 * target.m03 * target.m11;

		tmp[14] = -target.m00 * target.m11 * target.m32 +
			target.m00 * target.m12 * target.m31 +
			target.m10 * target.m01 * target.m32 -
			target.m10 * target.m02 * target.m31 -
			target.m30 * target.m01 * target.m12 +
			target.m30 * target.m02 * target.m11;

		tmp[3] = -target.m01 * target.m12 * target.m23 +
			target.m01 * target.m13 * target.m22 +
			target.m11 * target.m02 * target.m23 -
			target.m11 * target.m03 * target.m22 -
			target.m21 * target.m02 * target.m13 +
			target.m21 * target.m03 * target.m12;

		tmp[7] = target.m00 * target.m12 * target.m23 -
			target.m00 * target.m13 * target.m22 -
			target.m10 * target.m02 * target.m23 +
			target.m10 * target.m03 * target.m22 +
			target.m20 * target.m02 * target.m13 -
			target.m20 * target.m03 * target.m12;

		tmp[11] = -target.m00 * target.m11 * target.m23 +
			target.m00 * target.m13 * target.m21 +
			target.m10 * target.m01 * target.m23 -
			target.m10 * target.m03 * target.m21 -
			target.m20 * target.m01 * target.m13 +
			target.m20 * target.m03 * target.m11;

		tmp[15] = target.m00 * target.m11 * target.m22 -
			target.m00 * target.m12 * target.m21 -
			target.m10 * target.m01 * target.m22 +
			target.m10 * target.m02 * target.m21 +
			target.m20 * target.m01 * target.m12 -
			target.m20 * target.m02 * target.m11;

		float det = target.m00 * tmp[0] + target.m01 * tmp[4] + target.m02 * tmp[8] + target.m03 * tmp[12];

		if (det == 0)
			throw std::exception("不可逆矩阵");

		det = 1.0f / det;

		for (int i = 0; i < 16; i++)
			out->operator[](i) = tmp[i] * det;
	}

public:
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
} Matrix;
