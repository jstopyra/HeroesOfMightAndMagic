//Sprite.h
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL_image.h>
class TransformComponent;
#include "TransformComponent.h"
class GameObject;

class Sprite
{
	SDL_Rect m_rect;
	SDL_Texture* m_pTexture;
	TransformComponent* m_pTransform;
	GameObject* m_pParentObject;
	bool m_isFlipped;


public:
	Sprite(GameObject* parentObject, const char* pFileName);
	~Sprite();
	SDL_Rect* const GetRect(){ return &m_rect; }
	SDL_Texture* const GetTexture(){ return m_pTexture; }
	Component* GetComponent(int componentNum);
	TransformComponent* GetTransformComponent(){ return m_pTransform; }
	bool GetIsFlipped() { return m_isFlipped; }
	void Flip() {m_isFlipped = !m_isFlipped;}


};

#endif