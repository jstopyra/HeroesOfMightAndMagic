//RenderableComponent.h
#ifndef __RENDERABLECOMPONENT_H__
#define __RENDERABLECOMPONENT_H__
#include "Component.h"
class Sprite;
class RenderableComponent : public Component
{
	Sprite* m_pSprite;
	int m_renderLayer;

public:
	RenderableComponent(GameObject* parentGameObject, const char* spriteName, int renderLayer);
	virtual ~RenderableComponent();
	virtual bool Init() override;
	Sprite* GetSprite(){ return m_pSprite; }
	virtual void DeleteObject(GameObject* parent);
	void UpdateRect(int posX, int posY);
	void FlipRect();
protected:

private:

};

#endif