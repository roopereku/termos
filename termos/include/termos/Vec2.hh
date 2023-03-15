#ifndef TERMOS_VEC2_HH
#define TERMOS_VEC2_HH

namespace Termos {
template <typename T>
class Vec2
{
public:
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2() : x(0), y(0) {}

	T x;
	T y;
};
}

typedef Termos::Vec2 <unsigned> Point;
typedef Termos::Vec2 <unsigned> Size;

typedef Termos::Vec2 <float> Pointf;
typedef Termos::Vec2 <float> Sizef;

#endif
