//UnitComponent.h
#ifndef __UNITCOMPONENT_H__
#define __UNITCOMPONENT_H__
#include "Component.h"

class GameObject;

enum class Player;
class UnitComponent : public Component
{
	int m_unitId;
	int m_unitHealth;
	int m_unitAttack;
	Player m_myPlayer;
	int m_unitWalkDistance;
	int m_unitAttackDistance;
public:
	UnitComponent(Player currPlayer, GameObject* parentGameObject, int unitWalkDistance, int unitAttackDistance);
	virtual ~UnitComponent();
	virtual bool Init() override;
	virtual void DeleteObject(GameObject* parent);
	void TakeDamage(int damange);

	//setters
	void SetUnitAttack();
	void SetUnitId(int unitId){ m_unitId = unitId; }
	//getters
	int const GetUnitId(){ return m_unitId; }
	int const GetUnitAttack(){ return m_unitAttack; }
	int const GetUnitHealth(){ return m_unitHealth; }
	Player* const GetMyPlayer(){ return &m_myPlayer; }
	int const GetWalkDistance();
	int const GetAttackDistance();

protected:

private:

};

#endif