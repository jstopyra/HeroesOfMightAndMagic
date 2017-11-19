//GameManager.h
#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <map>
#include "GameObject.h"
#include "Tile.h"

class ObjectManager
{
	int m_selectedUnitId;
	bool m_selectedUnit;
public:
	ObjectManager();
	~ObjectManager();
	void AddObject(GameObject* gameObject);
	void SelectedUnit(Tile* tile);

	void PlaceUnit(Tile* pFirstTile, Tile* pSecondTile);
	bool MapContainsId(int id);
	void Init();
private:
	std::map<int, GameObject*> m_gameObjectMap;
};

#endif