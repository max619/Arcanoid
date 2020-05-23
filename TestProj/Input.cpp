#include "stdafx.h"
#include "Input.h"

void  Input::KeyDown(SDL_Keycode v){
	keyStates[v] = true;
}
void Input::KeyUp(SDL_Keycode v){
	keyStates[v] = false;
}

bool Input::GetInput(SDL_Keycode k)
{
	auto it = keyStates.find(k);
	if (it != keyStates.end())
		return it->second;
	return false;
}

Input& Input::Get()
{
	static Input inst;
	return inst;
}