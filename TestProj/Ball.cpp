#include "stdafx.h"
#include "Ball.h"
#include "Enemy.h"

void Ball::Setup()
{
	if (isInit)
		return;

	renderer = parent->AddComponent<RenderEllipseComponent>();
	transform = parent->AddComponent<TransformComponent>();
	collider = parent->AddComponent<ColliderComponent>();

	Reset();

	isInit = true;
}

void Ball::Reset()
{
	renderer->color = Color(128, 128, 255);
	direction = Vector<float>(.0f, 1.f).Normalized();
	transform->pos = Vector<float>(0.5f, 0.6f);
	collider->size = renderer->size;
}

void Ball::Update(float dt)
{
	auto enemiesSpwaner = parent->FindInSceneChild("Enemies");
	if (enemiesSpwaner)
	{
		auto& enemies = enemiesSpwaner->GetChildren();
		int countEnabled = 0;
		for (auto&& e : enemies)
		{
			if (e->Enabled())
			{
				countEnabled++;
				if (CheckCollisionAndUpdateDirection(e))
				{
					auto enemy = e->GetComponent<Enemy>();
					if (enemy)
						enemy->RegisterHit();
				}
			}
		}

		if (countEnabled == 0)
			ExitGame();

	}

	auto player = parent->FindInSceneChild("Player");
	if (player)
	{
		CheckCollisionAndUpdateDirection(player);
	}

	if (transform->pos.x < 0)
	{
		transform->pos.x = 0;
		UpdateDirection(Vector<float>(1.0f, 0.0f));
	}

	if (transform->pos.x > 1)
	{
		transform->pos.x = 1;
		UpdateDirection(Vector<float>(-1.0f, 0.0f));
	}

	if (transform->pos.y < 0)
	{
		transform->pos.y = 0;
		UpdateDirection(Vector<float>(0.0f, 1.0f));
	}

	if (transform->pos.y > 1)
		ExitGame();



	auto offset = direction * speed * dt;
	transform->pos += offset;
}

bool Ball::CheckCollisionAndUpdateDirection(std::shared_ptr<SceneNode>& ptr)
{
	auto otherCollider = ptr->GetComponent<ColliderComponent>();
	Vector<float> intersectionCenter;
	if (otherCollider && collider->Intersects(*otherCollider, intersectionCenter))
	{
		auto collisionNormal = intersectionCenter - otherCollider->GetColliderCenter();
		UpdateDirection(collisionNormal.Normalized());
		transform->pos += collisionNormal * 0.3f;
		return true;
	}
	return false;
}


void Ball::ExitGame()
{
	parent->FindInSceneChild("root")->Reset();

	//throw std::exception("Game finish");
}

void Ball::UpdateDirection(Vector<float> normal)
{
	direction = (direction - normal * 2.0f * (direction * normal)).Normalized();
}

