#pragma once
#include "stdafx.h"

#include "SceneNode.h"

#include "Types.h"
#include <algorithm>
#include "SDLExtensions.h"



class TransformComponent : public Component
{
public:
	TransformComponent() : pos(0.0f, 0.0f), scale(1.0f, 1.0f) {}

	Vector<float> pos, scale;
};

class RenderRectangleComponent : public Component
{
public:
	RenderRectangleComponent() :size(0.05f, 0.05f), color(255, 255, 255){}

	void Render(SDL_Renderer* renderer) override;
	Vector<float> size;
	Color color;
};


class RenderEllipseComponent : public Component
{
public:
	RenderEllipseComponent() :size(0.05f, 0.05f), color(255, 255, 255){}

	void Render(SDL_Renderer* renderer) override;
	Vector<float> size;
	Color color;
};

class ColliderComponent : public Component
{
public:
	bool Intersects(ColliderComponent& other, Vector<float>& intersectionPt);

	Vector<float> GetColliderCenter();
	Rectangle2D<float> GetColliderBounds();
	Vector<float> size, pos;

private:
	bool LineIntersection(Vector<float> a, Vector<float> aDir, Vector<float> b, Vector<float> bDir, Vector<float>& intersectionPt);
};