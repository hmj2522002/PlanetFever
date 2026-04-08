#pragma once
#include "Math.hpp"


// 参考：https://easings.net/ja
// ２つの値の間を補間
class Easing
{
private:
	template<typename T>
	static constexpr T Exec(const T begin, const T end, float t)
	{
		return static_cast<T>(begin * (1 - t) + end * t);
	}

public:
	template<typename T>
	static constexpr T EaseInCubic(const T begin, const T end, float t)
	{
		t = Math::Clamp01(t);
		return Exec(begin, end, t * t * t);
	}
};
