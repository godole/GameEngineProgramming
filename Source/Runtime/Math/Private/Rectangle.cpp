#include "Precompiled.h"

Rectangle::Rectangle(const std::vector<Vector2> InVertices)
{
	// 직접 구현해보시오.
	Vector2 min(INFINITY, INFINITY);
	Vector2 max(0.0f, 0.0f);

	for (auto itr = InVertices.begin(); itr != InVertices.end(); itr++)
	{
		min = Vector2(Math::Min((*itr).X, min.X), Math::Min((*itr).Y, min.Y));
		max = Vector2(Math::Max((*itr).X, max.X), Math::Max((*itr).Y, max.Y));
	}

	Min = min;
	Max = max;
}