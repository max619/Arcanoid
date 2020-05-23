#pragma once
#include "stdafx.h"

#include "GameObject.h"
#include <memory>

class SceneNode;
//#include "SceneNode.h"

class Component : public GameObject
{
public:
	Component() {};
	virtual ~Component() {};

	virtual void Setup() override{};
	virtual void Update(float dt)  override{};
	virtual void Render(SDL_Renderer* renderer)  override{};

	void SetParent(std::shared_ptr<SceneNode> parent)
	{
		this->parent = parent;
	}

protected:
	std::shared_ptr<SceneNode> parent;
};

