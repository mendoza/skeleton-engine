#ifndef SKELETON_VECTOR2_HPP
#define SKELETON_VECTOR2_HPP
#include <iostream>
namespace skeleton {
template <typename T> class Vector2 {
public:
  T x, y;
  Vector2() : x(0), y(0) {}
  Vector2(T x, T y) : x(x), y(y) {}
  Vector2 operator+(const Vector2 &v) const {
    return Vector2(x + v.x, y + v.y);
  }

  Vector2 operator-(const Vector2 &v) const {
    return Vector2(x - v.x, y - v.y);
  }

  Vector2 operator*(T s) const { return Vector2(x * s, y * s); }

  Vector2 operator/(T s) const { return Vector2(x / s, y / s); }

  bool operator==(const Vector2 &v) const { return x == v.x && y == v.y; }

  bool operator!=(const Vector2 &v) const { return x != v.x || y != v.y; }

  friend std::ostream &operator<<(std::ostream &os, const Vector2 &v) {
    return os << "(" << v.x << ", " << v.y << ")";
  }
};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
} // namespace skeleton
#endif
