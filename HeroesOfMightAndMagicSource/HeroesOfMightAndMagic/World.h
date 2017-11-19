//World.h
#ifndef __WORD_H__
#define __WORD_H__

#include "Tile.h"
#include "Constants.h"
class UnitComponent;

enum class Player;
class World
{
	//first selection used to move the object from tile to tile
	Tile* m_pFirstTile;
	//second selection used to move the object from tile to tile
	Tile* m_pSecondTile;

public:
	World();
	~World();
	void CheckMouseInput(int x, int y);
	Tile* GetTileByIndex(int tileIndex)	{return m_pGrid[tileIndex];}
	Tile* GetFirstEmptyTile(Player currPlayer);
	void DrawShadows();
protected:

private:
	//Array of the shadows created to simulate where player can move
	GameObject* m_pPositiveGrid[k_numGridRows * k_numGridColumns];
	//All the tiles in the game
	Tile* m_pGrid[k_numGridRows * k_numGridColumns];


	//Check the distance between 2 points
	float CheckTileDistance(int firstX, int firstY, int secondX, int secondY);
	void CheckTilePointer(Tile* pTile);	//Check whats under the tile
	void SelectedUnitTile(Tile* pTile, UnitComponent* pUnitComponent);
	void ClearPositiveGrid();	//clear the grid that simulates the player movement availability
	void TileClicked(Tile* pTile);	//THis is the clicked tile
	void WalkToTile(Tile* pTile);	//Move the unit to a specific tile

	//returns the tile of a specific index
	Tile* GetGridTile(int gridIndex){ return m_pGrid[gridIndex]; }

};

#endif