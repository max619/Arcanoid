#include "stdafx.h"
#include "Enemy.h"

void Enemy::Setup()
{
	if (isInit)
		return;

	colors =
	{
		Color(255, 0, 0),
		Color(255, 128, 128),
		Color(255, 255, 64),
		Color(64, 255, 64)
	};

	renderer = parent->AddComponent<RenderRectangleComponent>();
	transform = parent->AddComponent<TransformComponent>();
	collider = parent->AddComponent<ColliderComponent>();

	Reset();
	isInit = true;
}

void Enemy::Reset()
{
	counter = colors.size() - 1;
	renderer->color = colors[counter];

	parent->Enabled() = true;
}


void Enemy::RegisterHit()
{
	if (counter - 1 < 0)
		parent->Enabled() = false;
	else
		counter--;
}
void Enemy::Update(float dt)
{
	if (counter > 0)
		renderer->color = colors[counter];
}

void EnemySpawner::Setup()
{
	float xStep = ((maxX - minX) / cols);
	float yStep = ((maxY - minY) / rows);
	Vector<float> size(xStep - border, yStep - border);

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			auto node = parent->AddChildNode("Enemy");
			auto enemy = node->AddComponent<Enemy>();
			enemy->Setup();
			node->GetComponent<TransformComponent>()->pos = Vector<float>(minX + xStep * c + size.x * 0.5f, minY + yStep * r + size.y * 0.5f);
			node->GetComponent<RenderRectangleComponent>()->size = size;
			node->GetComponent<ColliderComponent>()->size = size;
		}
	}
}