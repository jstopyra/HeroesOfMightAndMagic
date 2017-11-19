//World.cpp
#include "World.h"
#include "Constants.h"
#include <math.h>
#include <SDL.h>
#include "Game.h"
#include "ObjectFactory.h"
#include "UnitComponent.h"
#include "SdlEngine.h"
World::World()
	: m_pFirstTile(nullptr)
	, m_pSecondTile(nullptr)
{
	//create the grid
	for (int i = 0; i < k_numGridRows * k_numGridColumns; ++i)
	{
		m_pGrid[i] = new Tile(i);
	}
}


World::~World()
{
	//delete the grid
	for (int i = 0; i < k_numGridRows * k_numGridColumns; ++i)
	{
		delete m_pGrid[i];
	}
}

void World::CheckMouseInput(int x, int y)
{
	Tile* returnTile;
	for (int i = 0; i < k_numGridRows * k_numGridColumns; ++i)
	{
		int tileX = m_pGrid[i]->GetPosX() + 34;
		int tileY = m_pGrid[i]->GetPosY() + 101;
		float distance = CheckTileDistance(tileX, tileY, x, y);
		if (distance < k_tileRadius)
		{
			//We have clicked on this tile, lets see whats on it.
			TileClicked(m_pGrid[i]);
			break;
		}
	}	
	returnTile;
}


float World::CheckTileDistance(int firstX, int firstY, int secondX, int secondY)
{
	float deltaX = (float)(firstX - secondX);
	float deltaY = (float)(firstY - secondY);
	deltaX *= deltaX;
	deltaY *= deltaY;
	return sqrt(deltaX + deltaY);
}

void World::TileClicked(Tile* pTile)
{
	//The tile is empty
	if (pTile->IsEmpty())
	{
		//see if we have anything selected;
		if (m_pFirstTile)
		{
			//see if the selected tile is in distance
			//Lets move to that position
			WalkToTile(pTile);
		}
	}
	else//There is something on that tile.
	{
		UnitComponent* pUnitComponent = static_cast<UnitComponent*>(pTile->GetUnit()->GetComponent(k_unitComponentNum));
		if (*pUnitComponent->GetMyPlayer() == Game::GetInstance()->GetCurrentPlayer())
		{
			//This is my unit. lets reselect.
			if (pTile != m_pFirstTile)
			SelectedUnitTile(pTile, pUnitComponent);
		}
		else if (m_pFirstTile)
		{
			m_pSecondTile = pTile;
			//This is not my unit. lets attack him.
			int firstX = m_pFirstTile->GetPosX();
			int firstY = m_pFirstTile->GetPosY();
			int secondX = m_pSecondTile->GetPosX();
			int secondY = m_pSecondTile->GetPosY();
			float distance = CheckTileDistance(firstX, firstY, secondX, secondY);
			UnitComponent* unitComponent = static_cast<UnitComponent*>(m_pFirstTile->GetUnit()->GetComponent(k_unitComponentNum));

			if (unitComponent->GetAttackDistance() > distance)
			{
				SdlEngine::GetInstance()->PlaySfx(SdlEngine::GetInstance()->GetAttackSfx());

				pUnitComponent->TakeDamage(unitComponent->GetUnitAttack());
				if (pUnitComponent->GetUnitHealth() <= 0)
				{
					pUnitComponent->GetParent()->Delete();

					pTile->AssignObject(nullptr);
					//Walk to the tile that the enemy was standing at
					WalkToTile(pTile);
				}
				else
				{
					//Walk to the same tile that we were just on so we can reset the map
					WalkToTile(m_pFirstTile);
				}
				m_pFirstTile = nullptr;
			}
			m_pSecondTile = nullptr;
		}
	}
}

//move the player to a given tile
void World::WalkToTile(Tile* tile)
{
	m_pSecondTile = tile;
	int firstX = m_pFirstTile->GetPosX();
	int firstY = m_pFirstTile->GetPosY();
	int secondX = m_pSecondTile->GetPosX();
	int secondY = m_pSecondTile->GetPosY();
	UnitComponent* unitComponent = static_cast<UnitComponent*>(m_pFirstTile->GetUnit()->GetComponent(k_unitComponentNum));

	float distance = CheckTileDistance(firstX, firstY, secondX, secondY);
	if (unitComponent->GetWalkDistance() > distance)
	{
		if (m_pFirstTile != m_pSecondTile)
			SdlEngine::GetInstance()->PlaySfx(SdlEngine::GetInstance()->GetStepSfx());
		Game::GetInstance()->GetObjectManager()->PlaceUnit(m_pFirstTile, m_pSecondTile);
		m_pFirstTile = nullptr;
		ClearPositiveGrid();
		DrawShadows();
	}
	m_pSecondTile = nullptr;
}

//Selects the gameobjects thats under the clicked tile
//checks if its the allie or an enemy
void World::SelectedUnitTile(Tile* tile, UnitComponent* pUnitComponent)
{
	SdlEngine::GetInstance()->PlaySfx(SdlEngine::GetInstance()->GetSelectSfx());
	ClearPositiveGrid();
	m_pFirstTile = tile;
	int myX = tile->GetPosX();
	int myY = tile->GetPosY();
	//Show the PositiveGrid(YEEEY)
	for (int i = 0; i < k_numGridColumns * k_numGridRows; ++i)
	{
		Tile* checkTile = Game::GetInstance()->GetWorld()->GetTileByIndex(i);
		int tileX = checkTile->GetPosX();
		int tileY = checkTile->GetPosY();
		//for movement
		pUnitComponent = static_cast<UnitComponent*>(m_pFirstTile->GetUnit()->GetComponent(k_unitComponentNum));
		float distance = CheckTileDistance(myX, myY, tileX, tileY);
		if (pUnitComponent->GetWalkDistance() > distance)
		{
			if (checkTile->IsEmpty())
			{
				m_pPositiveGrid[i] = ObjectFactory::GetInstance()->CreatePositiveGrid(k_pPositiveGrid, k_renderLayerPositiveGrid, checkTile);
			}
			else
			{
				//Check if it is enemy
				pUnitComponent = static_cast<UnitComponent*>(checkTile->GetUnit()->GetComponent(k_unitComponentNum));
				if (*pUnitComponent->GetMyPlayer() != Game::GetInstance()->GetCurrentPlayer())
				{
					if (pUnitComponent->GetAttackDistance() > distance)
						m_pPositiveGrid[i] = ObjectFactory::GetInstance()->CreatePositiveGrid(k_pNegativeGrid, k_renderLayerPositiveGrid, checkTile);
					else
					{
						m_pPositiveGrid[i] = ObjectFactory::GetInstance()->CreatePositiveGrid(k_pNeutralGrid, k_renderLayerPositiveGrid, checkTile);

					}
				}
			}
		}
	}
}

void World::DrawShadows()
{
	UnitComponent* unitComponent = nullptr;
	for (int i = 0; i < k_numGridColumns * k_numGridRows; ++i)
	{
		Tile* checkTile = Game::GetInstance()->GetWorld()->GetTileByIndex(i);
		if (!checkTile->IsEmpty())
		{
			unitComponent = static_cast<UnitComponent*>(checkTile->GetUnit()->GetComponent(k_unitComponentNum));
			//this is enemy shadow
			if (*unitComponent->GetMyPlayer() != Game::GetInstance()->GetCurrentPlayer())
			{
				m_pPositiveGrid[i] = ObjectFactory::GetInstance()->CreatePositiveGrid(k_pNeutralGrid, k_renderLayerPositiveGrid, checkTile);

			}
			//this is our shadow
			else
			{
				m_pPositiveGrid[i] = ObjectFactory::GetInstance()->CreatePositiveGrid(k_pPositiveGrid, k_renderLayerPositiveGrid, checkTile);

			}
		}

	}
}

void World::ClearPositiveGrid()
{
	for (int i = 0; i < k_numGridColumns * k_numGridRows; ++i)
	{
		if (m_pPositiveGrid[i])
		{
			m_pPositiveGrid[i]->Delete();
		}
	}
}


Tile* World::GetFirstEmptyTile(Player currPlayer)
{
	int checkIndex = 0;
	Tile* pCheckTile = nullptr;
	int rowDelta = 0;
	if (currPlayer != Player::k_left)
	{
		rowDelta = k_numGridColumns -1;
	}
	for (int i = 0; i < (k_numGridRows * k_numGridColumns); ++i)
	{
		int currentRow = i % (k_numGridRows);
		int currentColumn = (i / k_numGridRows) + rowDelta;
		checkIndex = (currentRow * k_numGridColumns) + currentColumn;
		pCheckTile = GetGridTile(checkIndex);
		if (pCheckTile->IsEmpty())
		{
			return pCheckTile;
		}
	}
	return nullptr;
}