#include "stdafx.h"
#include "BaseComponents.h"
#include <SDL2_gfxPrimitives.h>

void RenderRectangleComponent::Render(SDL_Renderer* renderer)
{
	int w, h;
	SDL_GetRendererOutputSize(renderer, &w, &h);

	auto transform = this->parent->GetComponent<TransformComponent>();

	Vector<float> offset(size.x * transform->scale.x * 0.5f, size.y * transform->scale.y * 0.5f);
	Vector<float> topLeft = transform->pos - offset;
	Vector<float> bottomRight = transform->pos + offset;

	Vector<int> topLefti(static_cast<int>(w * topLeft.x), static_cast<int>(h * topLeft.y));
	Vector<int> bottomRighti(static_cast<int>(w * bottomRight.x), static_cast<int>(h * bottomRight.y));

	topLefti.x = std::min(std::max(0, topLefti.x), w);
	topLefti.y = std::min(std::max(0, topLefti.y), h);


	bottomRighti.x = std::min(std::max(0, bottomRighti.x), w);
	bottomRighti.y = std::min(std::max(0, bottomRighti.y), h);

	SDLEx_SetRendererDrawingColor(renderer, color);
	SDL_Rect rect{ topLefti.x, topLefti.y, bottomRighti.x - topLefti.x, bottomRighti.y - topLefti.y };
	SDL_RenderFillRect(renderer, &rect);
};

void RenderEllipseComponent::Render(SDL_Renderer* renderer)
{
	int w, h;
	SDL_GetRendererOutputSize(renderer, &w, &h);

	auto transform = this->parent->GetComponent<TransformComponent>();

	Vector<float> offset(size.x * transform->scale.x * 0.5f, size.y * transform->scale.y * 0.5f);
	Vector<float> topLeft = transform->pos - offset;
	Vector<float> bottomRight = transform->pos + offset;

	
	filledEllipseRGBA(renderer, static_cast<short>(transform->pos.x * w), static_cast<short>(transform->pos.y * h),
		static_cast<short>(size.x * transform->scale.x * 0.5f * w), static_cast<short>(size.y * transform->scale.y * 0.5f * h),
		color.data[0], color.data[1], color.data[2], color.data[3]);
};



bool ColliderComponent::Intersects(ColliderComponent& other, Vector<float>& intersectionPt)
{
	auto thisCenter = GetColliderCenter();
	auto thisBounds = GetColliderBounds();

	auto otherCenter = other.GetColliderCenter();
	auto otherBounds = other.GetColliderBounds();

	if (thisBounds.Intersects(otherBounds))
	{
		auto dir = thisCenter - otherCenter;
		//left side
		{
			Vector<float> side(0.0f, thisBounds.top - thisBounds.bottom);
			Vector<float> startPoint(thisBounds.left, thisBounds.bottom);

			if (LineIntersection(otherCenter, dir, startPoint, side, intersectionPt))
				return true;
		}//top side
			{
				Vector<float> side(thisBounds.right - thisBounds.left, 0.f);
				Vector<float> startPoint(thisBounds.left, thisBounds.top);

				if (LineIntersection(otherCenter, dir, startPoint, side, intersectionPt))
					return true;
			}
			//right side
			{
				Vector<float> side(0.0f, thisBounds.top - thisBounds.bottom);
				Vector<float> startPoint(thisBounds.left, thisBounds.bottom);

				if (LineIntersection(otherCenter, dir, startPoint, side, intersectionPt))
					return true;
			}//bottom side
			{
				Vector<float> side(thisBounds.right - thisBounds.left, 0.f);
				Vector<float> startPoint(thisBounds.left, thisBounds.bottom);

				if (LineIntersection(otherCenter, dir, startPoint, side, intersectionPt))
					return true;
			}
			intersectionPt = thisCenter;
			return true;
	}

	return false;
}

Vector<float> ColliderComponent::GetColliderCenter()
{
	return parent->GetComponent<TransformComponent>()->pos + pos;
}

Rectangle2D<float> ColliderComponent::GetColliderBounds()
{
	auto center = GetColliderCenter();
	auto scale = parent->GetComponent<TransformComponent>()->scale;
	Vector<float> scaledSize(size.x * scale.x, size.y * scale.y);
	return Rectangle2D<float>(
		Vector<float>(center.x - scaledSize.x * 0.5f, center.y - scaledSize.y * 0.5f),
		Vector<float>(center.x + scaledSize.x * 0.5f, center.y + scaledSize.y * 0.5f));
}

bool ColliderComponent::LineIntersection(Vector<float> a, Vector<float> aDir, Vector<float> b, Vector<float> bDir, Vector<float>& intersectionPt)
{
	auto tu = (b - a).Cross(bDir);
	auto tb = aDir.Cross(bDir);
	if (tb == 0)
		return false;

	auto t = tu / tb;
	if (t >= 0 && t <= 1)
	{
		intersectionPt = a + aDir * t;
		return true;
	}

	return false;
}