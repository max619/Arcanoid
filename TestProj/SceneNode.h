#pragma once
#include "stdafx.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <exception>
#include "GameObject.h"
class Component;
#include "Component.h"


class SceneNode : public GameObject
{
public:
	SceneNode(std::string name);
	template<typename T, typename... VArgs>
	std::shared_ptr<T> AddComponent(VArgs&&... args);
	template<typename T>
	std::shared_ptr<T> GetComponent();

	std::shared_ptr<SceneNode> AddChildNode(std::string name);
	bool& Enabled();
	void SetParent(std::shared_ptr<SceneNode> parent);
	std::shared_ptr<SceneNode> GetParent();
	std::vector<std::shared_ptr<SceneNode>>& GetChildren();
	void Setup() override;
	void Reset() override;
	void Update(float dt) override;
	void Render(SDL_Renderer* renderer) override;
	std::shared_ptr<SceneNode> FindChild(std::string name);
	std::shared_ptr<SceneNode> FindInSceneChild(std::string name);
private:
	std::shared_ptr<SceneNode> parent;
	std::string name;
	bool enabled = true;
	std::vector<std::shared_ptr<SceneNode>> children;
	std::unordered_map<std::string, std::shared_ptr<Component>> components;
};

template<typename T, typename... VArgs>
inline std::shared_ptr<T> SceneNode::AddComponent(VArgs&&... args)
{
	auto name = typeid(T).name();
	if (components.find(name) != components.end())
		throw std::exception("Component already exists");
	auto ptr = std::make_shared<T>(std::forward<VArgs>(args)...);
	ptr->SetParent(std::static_pointer_cast<SceneNode>(this->shared_from_this()));
	components.emplace(name, ptr);
	return ptr;
}

template<typename T>
std::shared_ptr<T> SceneNode::GetComponent()
{
	auto it = components.find(typeid(T).name());
	if (it == components.end())
		return std::shared_ptr<T>();

	return std::static_pointer_cast<T>(it->second);
}