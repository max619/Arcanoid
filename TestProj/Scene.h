#pragma once
#include "stdafx.h"

#include "SceneNode.h"

class Scene : public GameObject
{
public:
	Scene();
	~Scene();


	void Setup() override;
	void Update(float dt) override;
	void Render(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<SceneNode> root;
};

