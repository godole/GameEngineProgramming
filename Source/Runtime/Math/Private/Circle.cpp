
#include "Precompiled.h"

Circle::Circle(const std::vector<Vector2> InVertices)
{
	Vector2 center;
	Vector2 sum;

	//�����߽��� �̿��� Center�� ����
	for (auto itr = InVertices.begin(); itr != InVertices.end(); itr++)
		sum += (*itr);

	center = sum / InVertices.size();

	float radius = 0.0f;

	//Center�� ���� �� �������� �Ÿ��� Radius�� ����
	for (auto itr = InVertices.begin(); itr != InVertices.end(); itr++)
		radius = Math::Max(radius, (center - (*itr)).Size());

	Center = center;
	Radius = radius;
}
