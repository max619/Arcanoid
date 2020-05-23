#pragma once
#include "stdafx.h"

#include "BaseComponents.h"
#include "SceneNode.h"

class Ball : public Component
{
public:
	void Setup() override;
	void Reset() override;
	void Update(float dt) override;

private:
	bool CheckCollisionAndUpdateDirection(std::shared_ptr<SceneNode>& ptr);
	void ExitGame();
	void UpdateDirection(Vector<float> normal);

	float speed = 0.5f;
	Vector<float> direction;
	std::shared_ptr<RenderEllipseComponent> renderer;
	std::shared_ptr<TransformComponent> transform;
	std::shared_ptr<ColliderComponent> collider;
	bool isInit = false;
};