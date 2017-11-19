//GameObject.h
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class Component;
#include <map>
class GameObject
{
	int m_objectId;
public:
	GameObject();
	~GameObject();
	bool hasTransform;
	int posY;
	void AddComponent(int compNum, Component* componentNumber);
	Component* GetComponent(int componentNum);
	void Init();
	int ReturnPosY(const GameObject* pGameObject);
	bool hasComponents;

	bool operator<(GameObject &rhs);

	void Delete();
	void SetId();
	int const GetId();
	void Move(int posX, int posY);
	void SecondInit();

protected:

private:
	std::map<int, Component*> m_componentMap;
	int ReturnPosY(GameObject* pGameObject);

};

#endif