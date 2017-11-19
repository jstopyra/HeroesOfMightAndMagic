//ComponentFactory.cpp
#include "ObjectFactory.h"
#include <iostream>
#include "RenderableComponent.h"
#include "TransformComponent.h"
#include "UnitComponent.h"
#include <SDL.h>
#include "Constants.h"
#include "Sprite.h"
#include "Game.h"
using std::cout;

//Creates a game objects, adds specified components to it. add the object to the manager, returns the object
GameObject* ObjectFactory::CreateGameObject(Player currPlayer, const char* spriteName, int renderLayer, bool renderableComponent
	, bool unitComponent, bool transformComponent)
{
	GameObject* returnGameObject = new GameObject();
	Component* returnComponent = nullptr;
	returnGameObject->Init();
	if (renderableComponent)
	{
		returnComponent = new RenderableComponent(returnGameObject, spriteName, renderLayer);
		returnGameObject->AddComponent(k_renderableComponentNum, returnComponent);
	}
	if (unitComponent)
	{
		int walkDistance = (rand() % 200) + 100;
		int attackDistance = (rand() % 200) + 100;
		if (attackDistance < walkDistance)
			attackDistance = walkDistance;
		attackDistance = k_tileRadius*2;
		returnComponent = new UnitComponent(currPlayer, returnGameObject, walkDistance, attackDistance);
		returnGameObject->AddComponent(k_unitComponentNum, returnComponent);
	}
	if (transformComponent)
	{
		returnComponent = new TransformComponent(currPlayer, returnGameObject);
		returnGameObject->AddComponent(k_transformComponentNum, returnComponent);
		returnGameObject->hasTransform = true;
		returnGameObject->SecondInit();
	}
	Game::GetInstance()->GetObjectManager()->AddObject(returnGameObject);
	return returnGameObject;
}


//creates the sprite and returns it
Sprite* ObjectFactory::CreateSprite(GameObject* parentObject, const char* spriteName)
{
	return new Sprite(parentObject, spriteName);
}
//creates the grid piece and returns it
GameObject* ObjectFactory::CreatePositiveGrid(const char* spriteName, int renderLayer, Tile* pTile)
{
	GameObject* returnGameObject = new GameObject();
	Component* returnComponent = nullptr;
	returnGameObject->Init();

	returnComponent = new RenderableComponent(returnGameObject, spriteName, renderLayer);
	returnGameObject->AddComponent(k_renderableComponentNum, returnComponent);


	returnComponent = new TransformComponent(returnGameObject, pTile);
	returnGameObject->AddComponent(k_transformComponentNum, returnComponent);
	returnGameObject->hasTransform = true;
	returnGameObject->SecondInit();


	Game::GetInstance()->GetObjectManager()->AddObject(returnGameObject);
	return returnGameObject;
}