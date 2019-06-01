#ifndef VECTOR2D_H_
#define VECTOR2D_H_

template <typename T>
struct Vector2D {
	T x, y;

	Vector2D() {}
	Vector2D(T v) : x(v), y(v) {}
	Vector2D(T x, T y): x(x), y(y) {}
	
	Vector2D operator+(const Vector2D& o) {
		return Vector2D{ x + o.x, y + o.y };
	}
	Vector2D operator+(const T& o) {
		return Vector2D{ x + o, y + o };
	}
	Vector2D& operator+=(const T& o) {
		x += o.x;
		y += o.y;
		return *this;
	}
	Vector2D operator-(const Vector2D& o) {
		return operator+(o * -1);
	}
	Vector2D operator-(const T& o) {
		return operator-(o * -1);
	}
	Vector2D operator*(T t) {
		return Vector2D{ x * t, y * t };
	}
	Vector2D operator/(T t) {
		return operator*(1/t);
	}
};

template <typename T>
inline Vector2D<T> operator*(T t, const Vector2D<T>& v) { return v * t; }

#endif // !VECTOR2D_H_