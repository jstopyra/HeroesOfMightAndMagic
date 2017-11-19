//Game.cpp
#include "Game.h"
#include "SdlEngine.h"
#include "ObjectFactory.h"
#include "Tile.h"


bool Game::Init()
{
	m_quit = false;
	m_currentPlayer = Player::k_left;
	return true;
}
Game::~Game()
{
	//
}

bool Game::RunMainLoop()
{
	Init();//Initialize myself
	m_objectManager.Init();//Initialize Object manager
	CreateUi();	//CreateUi
	PopulateGrid();	//Populate the grid with units
	m_world.DrawShadows();	//Draw the shadows under the units
	//Entire GameLoop lays here.!!
	while (SdlEngine::GetInstance()->GetEvent()->type != SDL_QUIT && !m_quit)
	{
		SdlEngine::GetInstance()->HandleEvent();
		Render();
	}
	return true;
}


//Create/replace UI player view
GameObject* Game::CreateUi()
{
	//Clear renderer layer for UI and make a new one;
	SdlEngine::GetInstance()->ClearRenderLayer(k_renderLayerUi);
	switch (GetCurrentPlayer())
	{
	case Player::k_left:
		return  ObjectFactory::GetInstance()->CreateGameObject(Player::k_left, k_pPlayerLeft, k_renderLayerUi, true, false, false);
	case Player::k_right:
		return  ObjectFactory::GetInstance()->CreateGameObject(Player::k_left, k_pPlayerRight, k_renderLayerUi, true, false, false);
		break;
	default:
		break;
	}
	return nullptr;

}

//Render Stuff
void Game::Render()
{
	SdlEngine::GetInstance()->Draw();
}

//Creates a unit and puts it in the first null grid tile on the correct side of the map
GameObject* Game::CreateUnit(Player currPlayer)
{
	int randNum = rand() % 5;
	switch (rand() % 4)
	{
	case 0:
		return ObjectFactory::GetInstance()->CreateGameObject(currPlayer, k_pCyclops, k_renderLayerUnits, true, true, true);
		break;
	case 1:
		return ObjectFactory::GetInstance()->CreateGameObject(currPlayer, k_pMagog, k_renderLayerUnits, true, true, true);
		break;
	case 2:
		return ObjectFactory::GetInstance()->CreateGameObject(currPlayer, k_pHeroDark, k_renderLayerUnits, true, true, true);
		break;
	case 3:
		return ObjectFactory::GetInstance()->CreateGameObject(currPlayer, k_pHeroSilver, k_renderLayerUnits, true, true, true);
		break;
	default:
		return nullptr;
		break;
	}
	return nullptr;
}

//Populate the grid with a given amount of units for each players' side
void Game::PopulateGrid()
{
	Player currPlayer = Player::k_left;
	for (int j = 0; j < 2; ++j)
	{
		for (int i = 0; i < k_unitsToSpawnLeft; ++i)
		{
			m_objectManager.AddObject(CreateUnit(currPlayer));
		}
		currPlayer = Player::k_right;
	}
}


void Game::SwitchPlayer()
{
	switch (GetCurrentPlayer())
	{
	case Player::k_left:
		m_currentPlayer = Player::k_right;
		break;
	case Player::k_right:
		m_currentPlayer = Player::k_left;
		break;
	default:
		break;
	}
	CreateUi();
}