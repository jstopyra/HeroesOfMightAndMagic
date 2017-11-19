//Tile.cpp
#include "Tile.h"
#include "Constants.h"
#include "SDL.h"
Tile::Tile(int tileIndex)
	: m_pGameObject(nullptr)
{
	//THis is the offset to the center of the click of the texture for X(so all the textures are unified
	int xOffset = 50;
	//THis is the offset to the center of the click of the texture for Y(so all the textures are unified
	int yOffset = 10;
	int indexX = tileIndex % k_numGridColumns;
	int indexY = tileIndex / k_numGridColumns;
	//Check if we want to offset the hexagons
	if (indexY % 2 == 0)
	{
		//This is the offset for the hexagon shift
		xOffset += 20;
	}
	//set the positions of the tile
	m_posX = (indexX * k_gridWidth) + xOffset;
	m_posY = (indexY * k_gridHeight) + yOffset;
}

Tile::~Tile()
{

}

int const Tile::GetPosX()
{
	return m_posX;
}

int const Tile::GetPosY()
{
	return m_posY;
}

bool const Tile::IsEmpty()
{
	return m_pGameObject == nullptr;
}

//Assign a given object to the tile
void Tile::AssignObject(GameObject* pGameObject)
{
	m_pGameObject = pGameObject;
}
