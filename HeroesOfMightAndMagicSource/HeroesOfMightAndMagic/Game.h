//Game.h
#ifndef __GAME_H__
#define __GAME_H__

#include "Singleton.h"
#include "World.h"
#include "ObjectManager.h"

//Used to determine which player's turn is it
enum class Player
{
	k_left,
	k_right
};

class Game : public Singleton<Game>
{

	World m_world;
	ObjectManager m_objectManager;
	Player m_currentPlayer;
	bool m_quit;	//determines if we want to quit the game

public:
	~Game();

	bool RunMainLoop();
	bool Init();

	void SwitchPlayer();
	void QuitGame(){ m_quit = true; }

	//Getters
	ObjectManager* const GetObjectManager(){ return &m_objectManager; }
	World* const GetWorld(){ return &m_world; }
	Player const GetCurrentPlayer(){ return m_currentPlayer; }

protected:

private:
	void Update();
	void Render();
	GameObject* CreateUnit(Player currPlayer);
	void PopulateGrid();	//populates the grid with given amount of units for each player
	GameObject* CreateUi();

};

#endif