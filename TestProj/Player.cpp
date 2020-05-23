#include "stdafx.h"
#include "Player.h"

void Player::Setup()
{
	transform = parent->AddComponent<TransformComponent>();
	renderer = parent->AddComponent<RenderRectangleComponent>();
	collider = parent->AddComponent<ColliderComponent>();

	//renderer->color = Color(255, 0, 0);
	Reset();
}

void Player::Reset()
{
	renderer->size = Vector<float>(0.15f, 0.05f);
	transform->pos = Vector<float>(0.5f, 0.95f);
	collider->size = renderer->size;
}

void Player::Update(float dt)
{
	if (Input::Get().GetInput(SDL_KeyCode::SDLK_RIGHT))
		transform->pos.x = std::min(transform->pos.x + speed * dt, 1.0f);
	else if (Input::Get().GetInput(SDL_KeyCode::SDLK_LEFT))
		transform->pos.x = std::max(transform->pos.x - speed * dt, 0.0f);
}