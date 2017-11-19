//Tile.h
#ifndef __TILE_H__
#define __TILE_H__

class GameObject;

class Tile
{
	GameObject* m_pGameObject;
	int m_posX;
	int m_posY;

public:
	Tile(int tileIndex);
	~Tile();
	void AssignObject(GameObject* pGameObject);

	//getters
	int const GetPosX();
	int const GetPosY();
	bool const IsEmpty();
	GameObject* GetUnit(){ return m_pGameObject; }

};
#endif