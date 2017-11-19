//TransformComponent.h
#ifndef __TRANSFORMCOMPONENT_H__
#define __TRANSFORMCOMPONENT_H__
#include "Component.h"


class GameObject;
class Tile;
enum class Player;
template<typename type>
class Vector3
{
public:
	Vector3(type startValue) : m_x(startValue), m_y(startValue), m_z(startValue){};
	~Vector3(){};
	type m_x;
	type m_y;
	type m_z;
};



class TransformComponent : public Component
{
	Vector3<int> m_position;
	Vector3<float> m_rotation;
	Vector3<float> m_scale;
	Vector3<int> m_forward;
	
public:
	TransformComponent(Player currPlayer, GameObject* parentGameObject);
	TransformComponent(GameObject* parentGameObject, Tile* pTile);
	virtual ~TransformComponent();
	virtual bool Init() override;

	Vector3<int>* const GetPosition(){ return &m_position; }
	Vector3<float>* const GetRotation(){ return &m_rotation; }
	Vector3<float>* const GetScale(){ return &m_scale; }
	Vector3<int>* const GetForward(){ return &m_forward; }
	void SetPosition(int posX, int posY);
	virtual void DeleteObject(GameObject* parent);
	void GotFlipped();
protected:

private:

};

#endif