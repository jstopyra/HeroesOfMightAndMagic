//TransformComponent.cpp
#include "TransformComponent.h"
#include "Game.h"


TransformComponent::TransformComponent(Player currPlayer, GameObject* parentGameObject)
	: m_position(0)
	, m_rotation(0)
	, m_scale(1)
	, m_forward(1)
{
	m_pParentObject = parentGameObject; 

	Tile* myTile = Game::GetInstance()->GetWorld()->GetFirstEmptyTile(currPlayer);
	if (currPlayer == Player::k_right)
	{
		//flip the character
		m_forward.m_x = -1;
	}
	if (myTile)
	{
		int posX = myTile->GetPosX();
		int posY = myTile->GetPosY();
		SetPosition(posX, posY);
		myTile->AssignObject(m_pParentObject);
	}
	else
	{
		delete this;
	}
}

TransformComponent::TransformComponent(GameObject* parentGameObject, Tile* pTile)
	: m_position(0)
	, m_rotation(0)
	, m_scale(1)
	, m_forward(1)
{
	m_pParentObject = parentGameObject;
	Tile* myTile = pTile;
	if (myTile)
	{
		int posX = myTile->GetPosX();
		int posY = myTile->GetPosY();
		SetPosition(posX, posY);
	}
	else
	{
		delete this;
	}
}

TransformComponent::~TransformComponent()
{
	//
}

bool TransformComponent::Init()
{
	return true;
}

void TransformComponent::SetPosition(int posX, int posY)
{
	m_position.m_x = posX;
	m_position.m_y = posY;
}

void TransformComponent::DeleteObject(GameObject* parent)
{

}


void TransformComponent::GotFlipped()
{
	m_forward.m_x = 1;

}