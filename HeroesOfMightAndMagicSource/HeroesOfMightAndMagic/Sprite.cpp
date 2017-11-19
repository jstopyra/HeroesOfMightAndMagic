//Sprite.cpp
#include "Sprite.h"
#include "SdlEngine.h"
#include "GameObject.h"
#include "Constants.h"

Sprite::Sprite(GameObject* parentObject, const char* pFileName)
	: m_pTexture(NULL)
	, m_pParentObject(parentObject)
{
	//create the rect
	SDL_RWops* rwop = SDL_RWFromFile(pFileName, "rb");
	SDL_Surface* m_surface = IMG_LoadPNG_RW(rwop);
	if (m_surface == NULL)
	{
		SDL_Log("Failed to load the surface %s", SDL_GetError());
	}
	m_pTexture = SDL_CreateTextureFromSurface(SdlEngine::GetInstance()->GetRenderer(), m_surface);
	if (m_pTexture == NULL)
	{
		SDL_Log("Failed to load the texture %s", SDL_GetError());
	}
	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = m_surface->w;
	m_rect.h = m_surface->h;
	SDL_FreeSurface(m_surface);
}


Sprite::~Sprite()
{
	//
}


Component* Sprite::GetComponent(int componentNum)
{
	return m_pParentObject->GetComponent(componentNum);
}