//ComponentFactory.h
#ifndef __COMPONENTFACTORY_H__
#define __COMPONENTFACTORY_H__

#include "Singleton.h"
#include "GameObject.h"
#include "Tile.h"
enum class Player;
class Sprite;

class ObjectFactory : public Singleton<ObjectFactory>
{

public:
	~ObjectFactory(){};
	//creates units/background/grid(I know, should Have seperated it) :((((( SAD FACE!!!
	virtual GameObject* CreateGameObject(Player currPlayer, const char* spriteName, int renderLayer, bool renderableComponent, bool unitComponent, bool transformComponent);
	//Creates sprites
	virtual Sprite* CreateSprite(GameObject* parentObject, const char* spriteName);
	//Create the visual grid pieces
	virtual GameObject* CreatePositiveGrid(const char* spriteName, int renderLayer, Tile* pTile);
private:

};

#endif