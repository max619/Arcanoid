#pragma once
#include "stdafx.h"

#include <memory>

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	virtual ~GameObject() {};

	virtual void Setup() {};
	virtual void Update(float dt) {};
	virtual void Render(SDL_Renderer* renderer) {};
	virtual void Reset() {};
};

