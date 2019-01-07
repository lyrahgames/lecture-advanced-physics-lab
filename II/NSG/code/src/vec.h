#ifndef __VEC_H__
#define __VEC_H__

#include <math.h>


template <class T>
struct vec2{
	union{
		struct{ T x,y; };
		T v[2];
	};

	vec2(T vec_x = 0, T vec_y = 0): x(vec_x), y(vec_y) {}
	vec2(const T vec[2]): x(vec[0]), y(vec[1]) {}

	// get reference to array element
	T& operator [](int idx) { return v[idx]; }
	const T& operator [](int idx) const { return v[idx]; } // const call

	// set vector from coordinates
	void set(T vec_x, T vec_y) { x = vec_x; y = vec_y; }

	// set both coordinates to equal value
	void set2(T value) { x = y = value; }

	// set vector from array
	void setv(const T vec[2]) { x = vec[0]; y = vec[1]; }

	// set vector from vector
	void setvec(const vec2<T> &vec) { x = vec.x; y = vec.y; }

	// normalize vector
	void setnorm() { const T tmp = 1.0f/mag(); x *= tmp; y *= tmp; }

	// negate vector
	void setneg() { x = -x; y = -y; }

	// set coordinates to invers
	void setinv() { x = 1/x; y = 1/y; }

	// cross product in 2d
	void setcross() { x = -y; y = x; }

	// set component product
	void setcomp(const vec2<T> &vec) { x *= vec.x; y *= vec.y; }

	// set component division
	void setcdiv(const vec2<T> &vec) { x /= vec.x; y /= vec.y; }

	// add vector
	void setadd(const vec2<T> &vec) { x += vec.x; y += vec.y; }
	void operator +=(const vec2<T> &vec) { setadd(vec); }

	// subtract vector
	void setsub(const vec2<T> &vec) { x -= vec.x; y -= vec.y; }
	void operator -=(const vec2<T> &vec) { setsub(vec); }

	// multiply with scalar value
	void setmult(T value) { x *= value; y *= value; }
	void operator *=(T value) { setmult(value); }

	// divide by scalar value
	void setdiv(T value) { x /= value; y /= value; }
	void operator /=(T value) { setdiv(value); }

	// set to maximum coordinates
	void setmaxvec(const vec2<T> &vec) { x = ((x < vec.x)?(vec.x):(x)); y = ((y < vec.y)?(vec.y):(y)); }

	// set to minimum coordinate
	void setminvec(const vec2<T> &vec) { x = ((x > vec.x)?(vec.x):(x)); y = ((y > vec.y)?(vec.y):(y)); }


	// get magnitude
	T mag() const { return sqrt(x*x + y*y); }

	// get squared magnitude
	T sqmag() const { return x*x + y*y; }

	// get product of all components
	T prod() const { return x*y; }

	// get normalized vector
	vec2<T> norm() const { const T tmp = 1.0f/mag(); return vec2<T>(tmp*x, tmp*y); }

	// get negative vector
	vec2<T> neg() const { return vec2<T>(-x, -y); }
	vec2<T> operator -() const { return neg(); }

	// get vector of inverse values
	vec2<T> inv() const { return vec2<T>(1/x, 1/y); }

	// get dot product of vectors
	friend T dot(const vec2<T> &vec_1, const vec2<T> &vec_2) { return vec_1.x*vec_2.x + vec_1.y*vec_2.y; }
	friend T operator *(const vec2<T> &vec_1, const vec2<T> &vec_2) { return dot(vec_1, vec_2); }

	// get cross product in 2d
	friend vec2<T> cross(const vec2<T> vec) { return vec2<T>(-vec.y, vec.x); }

	// get component product
	friend vec2<T> comp(const vec2<T> &vec_1, const vec2<T> &vec_2) { return vec2<T>(vec_1.x*vec_2.x, vec_1.y*vec_2.y); }

	// get component division
	friend vec2<T> cdiv(const vec2<T> &vec_1, const vec2<T> &vec_2) { return vec2<T>(vec_1.x/vec_2.x, vec_1.y/vec_2.y); }

	// add vectors
	friend vec2<T> add(const vec2<T> &vec_1, const vec2<T> &vec_2) { return vec2<T>(vec_1.x+vec_2.x, vec_1.y+vec_2.y); }
	friend vec2<T> operator +(const vec2<T> &vec_1, const vec2<T> &vec_2) { return add(vec_1, vec_2); }

	// subtract vectors
	friend vec2<T> sub(const vec2<T> &vec_1, const vec2<T> &vec_2) { return vec2<T>(vec_1.x-vec_2.x, vec_1.y-vec_2.y); }
	friend vec2<T> operator -(const vec2<T> &vec_1, const vec2<T> &vec_2) { return sub(vec_1, vec_2); }

	// multiply vector with scalar value
	friend vec2<T> mult(T value, const vec2<T> &vec) { return vec2<T>(value*vec.x, value*vec.y); }
	friend vec2<T> mult(const vec2<T> &vec, T value) { return mult(value, vec); }
	friend vec2<T> operator *(T value, const vec2<T> &vec) { return mult(value, vec); }
	friend vec2<T> operator *(const vec2<T> &vec, T value) { return mult(value, vec); }

	// divide vector by scalar value
	friend vec2<T> div(const vec2<T> &vec, T value) { return vec2<T>(vec.x/value, vec.y/value); }
	friend vec2<T> operator /(const vec2<T> &vec, T value) { return div(vec, value); }

	// get maximal vector
	friend vec2<T> maxvec(const vec2<T> &vec_1, const vec2<T> &vec_2) { return vec2<T>((vec_1.x < vec_2.x)?(vec_2.x):(vec_1.x), (vec_1.y < vec_2.y)?(vec_2.y):(vec_1.y)); }

	// get minimal vector
	friend vec2<T> minvec(const vec2<T> &vec_1, const vec2<T> &vec_2) { return vec2<T>((vec_1.x > vec_2.x)?(vec_2.x):(vec_1.x), (vec_1.y > vec_2.y)?(vec_2.y):(vec_1.y)); }
};

typedef vec2<float> vec2f;
typedef vec2<double> vec2d;
typedef vec2<unsigned char> vec2b; // byte vector
typedef vec2<unsigned int> vec2u;
typedef vec2<int> vec2i;
typedef vec2<long long> vec2l;
typedef vec2<unsigned long long> vec2ul;

// template <class T, class U>
// vec2<T> toVec2<T>(vec2<U> vec) { return vec2<T>((T)vec.x, (T)vec.y); }

// template <class T, class U>
// vec2<T> operator T(const vec2<U> &vec) { return vec2<T>((T)vec.x, (T)vec.y); }


#endif // __VEC_H__