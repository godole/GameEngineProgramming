#include "Precompiled.h"
#include "RenderingSoftwareInterface.h"
using namespace CK::DD;

// 핵심 로직 
bool QuadTree::Insert(const std::string& InKey, const Rectangle& InBound)
{
	//자식 노드일 경우 스플릿
	if (IsLeaf)
		Split();

	//하위 트리 중에 바운드 볼륨을 포함하는 트리 탐색
	QuadTree* containsSub = FindSubTree(InBound);

	//있다면 하위 트리에 추가(재귀)
	if (containsSub != nullptr)
		containsSub->Insert(InKey, InBound);

	//없다면 트리 노드에 추가
	else
		Nodes.push_back(TreeNode(InKey, InBound));

  
  return true;
}

void QuadTree::Clear()
{
}

void QuadTree::Query(const CK::Rectangle& InRectangleToQuery, std::vector<std::string>& InOutItems) const
{
	//영역과 충돌하지 않는다면 검사할 필요가 없음
	if (!Bound.Intersect(InRectangleToQuery))
		return;

	//트리 노드의 오브젝트를 추가
	for (auto itr = Nodes.begin(); itr != Nodes.end(); itr++)
	{
		if ((*itr).NodeBound.Intersect(InRectangleToQuery))
			InOutItems.push_back((*itr).NodeKey);
	}

	//하위 트리의 노드들도 추가
	for (QuadTree* subTree : SubTrees)
	{
		if(subTree != nullptr)
			subTree->Query(InRectangleToQuery, InOutItems);
	}
}

void QuadTree::Split()
{
	// SW, SE, NW, SE 네 개의 영역으로 쪼개고 이들의 바운딩 볼륨을 계산해서 넣기
	IsLeaf = false;

	Vector2 center;
	Vector2 extent;

	Bound.GetCenterAndExtent(center, extent);

	Rectangle NW = Rectangle(Bound.Min, center);
	Rectangle NE = Rectangle(Vector2(center.X, Bound.Min.Y), Vector2(Bound.Max.X, center.Y));
	Rectangle SW = Rectangle(Vector2(Bound.Min.X, center.Y), Vector2(center.X, Bound.Max.Y));
	Rectangle SE = Rectangle(center, Bound.Max);

	SubTrees[0] = new QuadTree(NW, Level + 1);
	SubTrees[1] = new QuadTree(NE, Level + 1);
	SubTrees[2] = new QuadTree(SW, Level + 1);
	SubTrees[3] = new QuadTree(SE, Level + 1);
}

bool QuadTree::Contains(const CK::Rectangle& InBox) const
{
	return Bound.IsInside(InBox);
}
 
QuadTree* QuadTree::FindSubTree(const Rectangle& InBound)
{
	// 네 개의 자식 노드를 돌면서 주어진 영역을 완전 포함하는 자식 트리가 있는지 조사.
	for (QuadTree* subTree : SubTrees)
	{
		assert(subTree != nullptr);
		if (subTree->Contains(InBound))
		{
			return subTree;
		}
	}

  // 없으면 겹친다고 판단하고 null 반환
	return nullptr;
}