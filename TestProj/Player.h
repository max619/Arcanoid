#pragma once
#include "stdafx.h"

#include "SceneNode.h"
#include "BaseComponents.h"
#include "Input.h"

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

class Player : public Component
{
public:
	void Setup() override;
	void Reset() override;
	void Update(float dt) override;

	float speed = 0.5f;

private:
	std::shared_ptr<TransformComponent> transform;
	std::shared_ptr<RenderRectangleComponent> renderer;
	std::shared_ptr<ColliderComponent> collider;

};

