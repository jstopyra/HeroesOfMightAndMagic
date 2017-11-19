//Author: Jakub Stopyra
//Date: 10/22/2015

//Program.cpp

//#include "vld.h"

#include <SDL.h>
#include <iostream>
#include "SdlEngine.h"
#include "ObjectFactory.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	//Initialize SDL, if anything goes bad, quit the program
	if (!SdlEngine::GetInstance()->Init())
	{	
		//Destroy the created singleton
		SdlEngine::GetInstance()->DestroySingleton();
		return -1;
	}
	//Run main loop of the game(Thats where the entire game logic happens)
	Game::GetInstance()->RunMainLoop();

	//Cleanup singletons when the game closes
	Game::GetInstance()->DestroySingleton();
	SdlEngine::GetInstance()->DestroySingleton();
	ObjectFactory::GetInstance()->DestroySingleton();
	return 0;
}