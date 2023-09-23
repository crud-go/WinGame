#pragma once
#include <iostream>
template <typename T>
class vec2
{
public:
	T x, y;
	vec2(T x, T y);
	vec2();

	vec2 operator + (const vec2<T>& o) const { return vec2<T>(x + o.x, y + o.y); }
	vec2 operator - (const vec2<T>& o) const { return vec2<T>(x - o.x, y - o.y); }
	friend std::ostream& operator << (std::ostream& io, const vec2<T>& o) { std::cout << "x: " << o.x << " y: " << o.y; return io; }
	vec2 operator * (const vec2<T>& o) const { return vec2<T>(x * o.x, y * o.y); }
	//vec2 operator / (const vec2<T>& o) const { return vec2<T>(x / o.x, y / o.y); }
	vec2<T>& operator += (const vec2<T>& o) { x += o.x; y += o.y; return *this; }
	friend vec2<T> operator * (float o, const vec2<T>& t) { return vec2<T>(o * t.x, o * t.y); }
	friend vec2<T> operator * (const vec2<T>& o, float t) { return vec2<T>(o.x * t, o.y * t); }
	friend vec2<T> operator / (float o, const vec2<T>& t) { return vec2<T>(o / t.x, o / t.y); }
	friend vec2<T> operator / (const vec2<T>& o, float t) { return vec2<T>(o.x / t, o.y / t); }


};

template <typename T>
class vec3
{
public:
	T x, y,z;
	vec3(T x, T y, T z);
	vec3();

	vec3 operator + (const vec3<T>& o) const { return vec3<T>(x + o.x, y + o.y, z+o.z); }
	vec3 operator - (const vec3<T>& o) const { return vec3<T>(x - o.x, y - o.y, z+o.z); }
	friend std::ostream& operator << (std::ostream& io, const vec3<T>& o) { std::cout << "x: " << o.x << " y: " << o.y<<" z: "<<o.z; return io; }


};
template <typename T>
class colorVec4
{
public:
	T r, g, b, a;
	colorVec4(T _r, T _g, T _b, T _a);
	colorVec4();

};




template<typename T>
inline vec2<T>::vec2(T _x, T _y)
{
	x = _x;
	y = _y;
}

template<typename T>
inline vec2<T>::vec2()
{
	x = y = 0;
}

template<typename T>
inline vec3<T>::vec3(T _x, T _y ,T _z)
{
	x = _x;
	y = _y;
	z = _z;

}

template<typename T>
inline vec3<T>::vec3()
{
	x = y = z = 0;
}

template<typename T>
inline colorVec4<T>::colorVec4(T _r, T _g, T _b, T _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;

}

template<typename T>
inline colorVec4<T>::colorVec4()
{
	r = g = b = a = 0;
}
