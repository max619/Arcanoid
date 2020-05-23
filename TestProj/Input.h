#pragma once
#include "stdafx.h"
#include <unordered_map>

class Input
{
public:
	void KeyDown(SDL_Keycode v);
	void KeyUp(SDL_Keycode v);
	bool GetInput(SDL_Keycode k);
	static Input& Get();
private:
	Input() {};
	std::unordered_map<SDL_Keycode, bool> keyStates;
};