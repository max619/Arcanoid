#pragma once
#include "stdafx.h"

#include "BaseComponents.h"

class Enemy : public Component
{
public:
	void Setup() override;
	void Reset() override;
	void RegisterHit();
	void Update(float dt) override;
private:
	std::shared_ptr<RenderRectangleComponent> renderer;
	std::shared_ptr<TransformComponent> transform;
	std::shared_ptr<ColliderComponent> collider;
	int counter = 4;

	std::vector<Color> colors;
	bool isInit = false;
};

class EnemySpawner : public Component
{
public:
	void Setup() override;

	int rows = 3, cols = 10;
	float minX = 0.1f, maxX = 0.9f, minY = 0.1f, maxY = 0.5f, border = 0.01f;
};