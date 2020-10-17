
#include "Precompiled.h"

Circle::Circle(const std::vector<Vector2> InVertices)
{
	Vector2 center;
	Vector2 sum;

	//무게중심을 이용해 Center를 구함
	for (auto itr = InVertices.begin(); itr != InVertices.end(); itr++)
		sum += (*itr);

	center = sum / InVertices.size();

	float radius = 0.0f;

	//Center와 가장 먼 정점과의 거리를 Radius로 정함
	for (auto itr = InVertices.begin(); itr != InVertices.end(); itr++)
	{
		float distance = (center - (*itr)).Size();

		if (radius < distance)
			radius = distance;
	}

	Center = center;
	Radius = radius;
}
