#include "stdafx.h"
#include "Scene.h"
#include "BaseComponents.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}


void Scene::Setup()
{
	root = std::make_shared<SceneNode>("root");
	/*auto transform = root->AddComponent<TransformComponent>();
	transform->pos = Vector<float>(0.5f, 0.5f);
	auto renderer = root->AddComponent<RenderRectangleComponent>();*/

	auto player = root->AddChildNode("Player");
	player->AddComponent<Player>();
	auto enemies = root->AddChildNode("Enemies");
	enemies->AddComponent<EnemySpawner>();
	auto ball = root->AddChildNode("Ball");
	ball->AddComponent<Ball>();


	root->Setup();
}

void Scene::Render(SDL_Renderer* renderer)
{
	root->Render(renderer);
}
void Scene::Update(float dt)
{
	if (Input::Get().GetInput(SDL_KeyCode::SDLK_F5))
		root->Reset();

	root->Update(dt);
}