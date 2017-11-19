//GameManager.cpp
#include "ObjectManager.h"
#include "Constants.h"
#include "UnitComponent.h"
#include "TransformComponent.h"
#include "ObjectFactory.h"
#include "Game.h"
#include "SdlEngine.h"

ObjectManager::ObjectManager()
	: m_selectedUnitId(0)
	, m_selectedUnit(false)
{

}


ObjectManager::~ObjectManager()
{
	//destroy the map
	std::map<int, GameObject*>::iterator itr;
	itr = m_gameObjectMap.begin();
	while (itr != m_gameObjectMap.end())
	{
		delete itr->second;
		itr++;
	}
	m_gameObjectMap.clear();
}

void ObjectManager::Init()
{
	//create the background
	ObjectFactory::GetInstance()->CreateGameObject(Player::k_left, k_pHeroesBg, k_renderLayerBackground, true, false, false);

	//create the grid 
	ObjectFactory::GetInstance()->CreateGameObject(Player::k_left, k_pGrid, k_renderLayerGrid, true, false, false);

}


//Add gameobject to the map of gameObjectrs
void ObjectManager::AddObject(GameObject* pGameObject)
{
	
	m_gameObjectMap[pGameObject->GetId()] = pGameObject;
}

//Checck if the map already has a given ID
bool ObjectManager::MapContainsId(int id)
{
	return m_gameObjectMap.find(id) != m_gameObjectMap.end();
}



//Takes a given tile and a gameObject.
//Take the tile that the gameObject is on and make it null;
//will put the gameobject on the tile's pointer.;
//Will take the tile's transform and give it to the GameObject
void ObjectManager::PlaceUnit(Tile* pFirstTile, Tile* pSecondTile)
{
	GameObject* pUnit = pFirstTile->GetUnit();
	pFirstTile->AssignObject(nullptr);
	pSecondTile->AssignObject(pUnit);
	pUnit->Move(pSecondTile->GetPosX(), pSecondTile->GetPosY());
	Game::GetInstance()->SwitchPlayer();
}
