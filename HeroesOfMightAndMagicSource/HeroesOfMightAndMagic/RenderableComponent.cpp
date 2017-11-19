//RenderableComponent.cpp
#include "RenderableComponent.h"
#include "SdlEngine.h"
#include "Sprite.h"


RenderableComponent::RenderableComponent(GameObject* parentGameObject, const char* spriteName, int renderLayer)
	:m_pSprite(nullptr)
	, m_renderLayer(renderLayer)
{
	m_pParentObject = parentGameObject;
	m_pSprite = SdlEngine::GetInstance()->CreateSprite(parentGameObject, spriteName, renderLayer);
}


RenderableComponent::~RenderableComponent()
{
	delete m_pSprite;
	m_pSprite = nullptr;

}

bool RenderableComponent::Init()
{
	return true;
}

void RenderableComponent::DeleteObject(GameObject* pParent)
{
	SdlEngine::GetInstance()->RemoveSprite(pParent, m_renderLayer);
}

void RenderableComponent::UpdateRect(int posX, int posY)
{
	SDL_Rect* pRect = m_pSprite->GetRect();
	pRect->x = posX;
	pRect->y = posY;
	if (pRect->w < 0)
	{
		pRect->x -= pRect->w;
	}
}


void RenderableComponent::FlipRect()
{
	m_pSprite->Flip();
}