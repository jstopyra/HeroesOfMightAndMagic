//Component.h
#ifndef __COMPONENT_H__
#define __COMPONENT_H__
class GameObject;
class Component
{

public:
	Component(){};
	virtual ~Component() { }
	virtual bool Init() = 0;
	virtual void Update() { }
	virtual GameObject* GetParent(){ return m_pParentObject; }
	virtual void DeleteObject(GameObject* parent) = 0;
protected:
	GameObject* m_pParentObject;

private:

};
#endif