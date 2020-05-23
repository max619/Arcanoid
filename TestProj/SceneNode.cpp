#include "stdafx.h"
#include "Player.h"


SceneNode::SceneNode(std::string name) : name(name){}

std::shared_ptr<SceneNode> SceneNode::AddChildNode(std::string name)
{
	auto ptr = std::make_shared<SceneNode>(name);
	ptr->SetParent(std::static_pointer_cast<SceneNode>(this->shared_from_this()));
	children.push_back(ptr);
	return ptr;
}

bool& SceneNode::Enabled() { return enabled; }

void SceneNode::SetParent(std::shared_ptr<SceneNode> parent)
{
	this->parent = parent;
}
std::shared_ptr<SceneNode> SceneNode::GetParent()
{
	return parent;
};

std::vector<std::shared_ptr<SceneNode>>& SceneNode::GetChildren()
{
	return children;
};

void SceneNode::Setup()
{
	for (auto&& comp : components)
		comp.second->Setup();

	for (auto&& child : children)
		child->Setup();
};


void SceneNode::Reset()
{
	for (auto&& comp : components)
		comp.second->Reset();

	for (auto&& child : children)
		child->Reset();
};
void SceneNode::Update(float dt)
{
	if (!enabled)
		return;
	for (auto&& comp : components)
		comp.second->Update(dt);

	for (auto&& child : children)
		child->Update(dt);
}
void SceneNode::Render(SDL_Renderer* renderer)
{

	if (!enabled)
		return;
	for (auto&& comp : components)
		comp.second->Render(renderer);

	for (auto&& child : children)
		child->Render(renderer);
};
std::shared_ptr<SceneNode> SceneNode::FindChild(std::string name)
{
	if (name.compare(this->name) == 0)
		return std::static_pointer_cast<SceneNode>(this->shared_from_this());

	for (auto& child : children)
	{
		auto res = child->FindChild(name);
		if (res)
			return res;
	}

	return std::shared_ptr<SceneNode>();
}

std::shared_ptr<SceneNode> SceneNode::FindInSceneChild(std::string name)
{
	std::shared_ptr<SceneNode> root = parent;
	while (root && root->GetParent())
	{
		root = root->GetParent();
	}

	if (root)
		return root->FindChild(name);
	return this->FindChild(name);
}