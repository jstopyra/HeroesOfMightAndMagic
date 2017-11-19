//Renderer.h
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Singleton.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <map>

class Sprite;
class GameObject;
class SdlEngine : public Singleton<SdlEngine>
{
	//Renderer Stuff
	std::map<int, GameObject*> m_spriteMap[k_numRenderLayers];	//Map of all the gameObjects that want to be rendered
	SDL_Window* m_pWindow;		//Our game window
	SDL_Renderer* m_pRenderer;	//Our renderer
	SDL_Event* m_pEvent;		//event poll
	bool m_mouseClicked;		//Need to know if we have already clicked, so we dont select stuff without wanting to 

	//Sound pointers
	Mix_Music* m_pBgMusic;
	Mix_Chunk* m_pAttackSfx;
	Mix_Chunk* m_pSelectSfx;
	Mix_Chunk* m_pStepSfx;


public:
	virtual ~SdlEngine();
	bool Init();	//Initialize the SDL with audio and video
	void Draw();	//Draw will take care of clearing the screen/ preparing a fresh one/ and rendering the new one
	Sprite* CreateSprite(GameObject* pParentGameObject, const char* pSpriteName, int renderLayer);
	void HandleEvent();	//pulls the windows events
	void RemoveSprite(GameObject* pGameObject, int randerLayer);	//removes the given sprite from the given renderlayer
	void ClearRenderLayer(int randerLayer);	//clears the given renderlayer

	void PlaySfx(Mix_Chunk* pChunkToPlay);	//Play the given mix chunk


	//Getters
	SDL_Event* const GetEvent() { return m_pEvent; }
	Mix_Chunk* const GetAttackSfx(){ return m_pAttackSfx; }
	Mix_Chunk* const GetSelectSfx(){ return m_pSelectSfx; }
	Mix_Chunk* const GetStepSfx(){ return m_pStepSfx; }
	SDL_Renderer* const GetRenderer(){ return m_pRenderer; }

private:
	void RegisterGameObject(GameObject* pGameObject, int renderLayer);	//Register the given Gameobject to a given renderLayer
	void RenderSprite(Sprite* pSprite);	//render the given sprite
	void ClearRender();					//clear the renderer
	void PrepareRender();				//Prepare the renderer with new sprites
	void PushRender();					//render the images on the screen
	bool LoadSounds();
	Mix_Music* LoadMusic(const char* pSoundName);	//Load the music with a given name
	Mix_Chunk* LoadWav(const char* pSoundName);	//load a Wav file with a given name
};

#endif