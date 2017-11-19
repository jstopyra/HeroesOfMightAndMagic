//GameObject.cpp
#include "GameObject.h"
#include "Component.h"
#include "Constants.h"
#include "TransformComponent.h"
#include "RenderableComponent.h"
#include "Game.h"


GameObject::GameObject()
	: hasTransform(false)
	, posY(0)
	, hasComponents(false)
	, m_objectId(0)
{
}


GameObject::~GameObject()
{
	//delete its components
	std::map<int, Component*>::iterator itr;
	itr = m_componentMap.begin();
	while (itr != m_componentMap.end())
	{
		delete itr->second;
		itr++;
	}
	m_componentMap.clear();
}

void GameObject::Init()
{
	//creates a random ID
	int randomId = 0;
	while (Game::GetInstance()->GetObjectManager()->MapContainsId(randomId) || randomId == 0)
	{
		randomId = rand() % 10000;
	}
	m_objectId = randomId;
}

//Makes sure the renderer and transform are unified after creation
void GameObject::SecondInit()
{
	//take the transform and read the x and y pos
	TransformComponent* transformComponent = static_cast<TransformComponent*>(GetComponent(k_transformComponentNum));
	int posX = transformComponent->GetPosition()->m_x;
	int posY = transformComponent->GetPosition()->m_y;
	int forwardX = transformComponent->GetForward()->m_x;
	//Change the rect of the component
	RenderableComponent* renderComponent = static_cast<RenderableComponent*>(GetComponent(k_renderableComponentNum));
	renderComponent->UpdateRect(posX, posY);
	if (forwardX < 0)
	{
		renderComponent->FlipRect();
	}

}

//adds a given component
void GameObject::AddComponent(int compNum, Component* component)
{
	m_componentMap[compNum] = component;
	hasComponents = true;
}

//returns component that were looking for
Component* GameObject::GetComponent(int componentNum)
{
		auto findIt = m_componentMap.find(componentNum);
		if (findIt == m_componentMap.end())
		{
			// not found
			return nullptr;
		}
		else
		{
			// found
			return findIt->second;
		}
	return nullptr;
}


void GameObject::Delete()
{
	//removes the sprite from the renderer
	m_componentMap[1]->DeleteObject(this);
}


int const GameObject::GetId()
{
	return m_objectId;
}
//adjust the rect to teh given position
void GameObject::Move(int posX, int posY)
{
	//Change the transform of the component.
	TransformComponent* transformComponent = static_cast<TransformComponent*>(GetComponent(k_transformComponentNum));
	transformComponent->SetPosition(posX, posY);
	//Change the rect of the component
	RenderableComponent* renderComponent = static_cast<RenderableComponent*>(GetComponent(k_renderableComponentNum));
	renderComponent->UpdateRect(posX, posY);
}