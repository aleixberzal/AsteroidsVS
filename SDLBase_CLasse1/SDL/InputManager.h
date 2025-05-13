#pragma once
#include <SDL.h>
#include <map>
#include "Utils.h"
//Keyboard has 4 states (4 flags)

enum KeyState {EMPTY, DOWN, UP, HOLD};

#define IM InputManager::Instance()//Class instance

class InputManager {
	//Singleton Patron

private:
	
	//SDL usees Sint32 to define the KEYBOARD
	std::map< Sint32,KeyState >keys;
	//MOUSE
	Vector2int mousePos;
	bool leftClick;
	//CLOSE
	bool quitGame = false;

public: 
	//GETTERS

	Vector2int GetMousePos() { return mousePos; }
	bool GetQuit() { return quitGame; }
	bool LeftClick() { return leftClick; }
	bool GetKey(Sint32 key, KeyState state) { return keys[key == state]; }
	
	void Listen();

	//Minimum needs to have a singleton class
	static InputManager& Instance() {
		static InputManager manager;
		return manager;
	}

};