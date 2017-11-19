//UnitComponent.cpp
#include "UnitComponent.h"
#include "GameObject.h"

UnitComponent::UnitComponent(Player currPlayer, GameObject* parentGameObject, int unitWalkDistance, int unitAttackDistance)
	: m_unitId(0)
	, m_myPlayer(currPlayer)
	, m_unitWalkDistance(unitWalkDistance)
	, m_unitAttackDistance(unitAttackDistance)
	, m_unitHealth(100)
	, m_unitAttack(50)
{
	m_pParentObject = parentGameObject;
}


UnitComponent::~UnitComponent()
{
	//
}

bool UnitComponent::Init()
{
	return true;
}


void UnitComponent::DeleteObject(GameObject* parent)
{

}

int const UnitComponent::GetWalkDistance()
{
	return m_unitWalkDistance;
}
int const UnitComponent::GetAttackDistance()
{
	return m_unitAttackDistance;
}


void UnitComponent::TakeDamage(int damage)
{
	//Attacked that player.
	m_unitHealth -= damage;
}
