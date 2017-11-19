//Renderer.cpp
#include "SdlEngine.h"
#include <SDL_Mixer.h>
#include <SDL_image.h>
#include "Sprite.h"
#include "ObjectFactory.h"
#include "RenderableComponent.h"
#include "Game.h"
#include <algorithm>

bool SdlEngine::Init()
{
	m_mouseClicked = false;
	//Initialize video and audio of SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_Log("Couldnt initialize SDL: %s", SDL_GetError());
		return false;
	}
	SDL_Log("SDL initialized correctly");
	//Opening audio channels and setting frequency
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
	{
		SDL_Log("FAILED to Open the audio\n");
		SDL_Log(Mix_GetError());
		return false;
	}

	//loading the music and sound effects
	LoadSounds();

	m_pWindow = NULL;
	m_pRenderer = NULL;
	m_pEvent = NULL;

	//Create the window for the game.
	m_pWindow = SDL_CreateWindow("Heroes of Might and Magic", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	if (m_pWindow == NULL)
	{
		SDL_Log("Failed to create the window %s", SDL_GetError());
		return false;
	}
	//Create the renderer the game will be using to display images to the window
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	//create an even poll
	m_pEvent = new SDL_Event();
	//return true when all the initialization completed
	return true;
}

SdlEngine::~SdlEngine()
{
	//Clearing all the SDL stuff
	Mix_FreeMusic(m_pBgMusic);
	Mix_FreeChunk(m_pAttackSfx);
	Mix_FreeChunk(m_pSelectSfx);
	Mix_FreeChunk(m_pStepSfx);
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	Mix_Quit();
	SDL_CloseAudio();
	delete m_pEvent;
}

void SdlEngine::Draw()
{
	//Clearing the previous frame
	ClearRender();
	//prepare the frame were gonna be rendering
	PrepareRender();
	//render the screen
	PushRender();
}

void SdlEngine::ClearRender()
{
	//pull the new event
	SDL_PollEvent(m_pEvent);
	//Clear the renderer
	SDL_RenderClear(m_pRenderer);
}

void SdlEngine::PrepareRender()
{
	//Loop through all render layers, sort their content and render it
	for (int i = 0; i < k_numRenderLayers; ++i)
	{
		//iterate throguh the map and add the sprite to the renderer
		std::map<int, GameObject*>::iterator itr;
		itr = m_spriteMap[i].begin();
		while (itr != m_spriteMap[i].end())
		{
			//Go through all the registered sprites and pushing their rect onto the renderer
			RenderableComponent* renderable = nullptr;
			renderable = static_cast<RenderableComponent*>(itr->second->GetComponent(k_renderableComponentNum));
			RenderSprite(renderable->GetSprite());
			itr++;
		}
	}
}

//Remove a specific GameObject with a given renderLayer;
void SdlEngine::RemoveSprite(GameObject* pGameObject, int renderLayer)
{
	if (pGameObject)
	{
		int objectId = pGameObject->GetId();
		m_spriteMap[renderLayer].erase(objectId);
	}
}

//Clear the entire given render layer
void SdlEngine::ClearRenderLayer(int renderLayer)
{
	m_spriteMap[renderLayer].clear();
}

//Push the given sprite onto the renderer
void SdlEngine::RenderSprite(Sprite* pSprite)
{
	//Get the rect of the sprite
	SDL_Rect* rect = pSprite->GetRect();
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (pSprite->GetIsFlipped())
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	//create the center point of the rect
	SDL_Point center;
	center.x = rect->x + rect->w / 2;
	center.y = rect->y + rect->h / 2;

	//Set the flip of the object to none(Something broke and I need it in here, otherwise my sprites go nuts)
	
	//Add the rect to the renderer
	SDL_RenderCopyEx(m_pRenderer, pSprite->GetTexture(), NULL, rect, 0, &center, flip);
}


//presenting the accumulated screen image
void SdlEngine::PushRender()
{
	SDL_RenderPresent(m_pRenderer);
}

//Loads the sprite of a given name and calls a RegisterSprite to register it to renderables.
Sprite* SdlEngine::CreateSprite(GameObject* parentObject, const char* spriteName, int renderLayer)
{
	//Create the sprite with the ObjectFactory
	Sprite* returnSprite = ObjectFactory::GetInstance()->CreateSprite(parentObject, spriteName);
	RegisterGameObject(parentObject, renderLayer);
	return returnSprite;
}

//Takes the given GameObject pointer and puts it in the given render layer
void SdlEngine::RegisterGameObject(GameObject* pGameObject, int renderLayer)
{
	//Get the id of the GameObject
	int id = pGameObject->GetId();
	//Make sure that the given renderlayer is in bounds
	if (renderLayer < k_numRenderLayers && renderLayer >= 0)
		m_spriteMap[renderLayer][id] = pGameObject;
}

//Handle the SDL events.
void SdlEngine::HandleEvent()
{
	if (m_pEvent->type == SDL_MOUSEBUTTONDOWN)
	{
		m_mouseClicked = true;
	}
	else if (m_pEvent->type == SDL_MOUSEBUTTONUP)
	{
		//If we clicked, Check if we have clicked on anything, Game will take care of that, Give it mouse x,y coordinates
		if (m_mouseClicked)
		{
			m_mouseClicked = false;
			//Mouse button was clicked. Check if any tile is close to it.
			int x, y;
			SDL_GetMouseState(&x, &y);

			Game::GetInstance()->GetWorld()->CheckMouseInput(x, y);
		}
	}
	else if (m_pEvent->type == SDL_KEYDOWN)
	{
		//quit the game when escape button is pressed
		if (m_pEvent->key.keysym.sym == SDLK_ESCAPE)
			Game::GetInstance()->QuitGame();
	}
}

//Load all the needed sounds for the game return false if anything fails
bool SdlEngine::LoadSounds()
{
	//Load background music
	m_pBgMusic = LoadMusic(k_pBgMusic);
	if (!m_pBgMusic)
	{
		return false;
	}
	//Load attackSfx
	m_pAttackSfx = LoadWav(k_pAttackSfx);
	if (m_pAttackSfx == nullptr)
	{
		return false;
	}
	//Load selectionSfx
	m_pSelectSfx = LoadWav(k_pSelectSfx);
	if (m_pSelectSfx == nullptr)
	{
		return false;
	}
	//Load stepSfx
	m_pStepSfx = LoadWav(k_pStepSfx);
	if (m_pStepSfx == nullptr)
	{
		return false;
	}
	return true;
}

//Play a given mixChunk
void SdlEngine::PlaySfx(Mix_Chunk* pChunkToPlay)
{
	Mix_PlayChannel(3, pChunkToPlay, 0);
}

//Load a music with the given string Name
Mix_Music* SdlEngine::LoadMusic(const char* pSoundName)
{
	Mix_Music* pMusic = nullptr;
	pMusic = Mix_LoadMUS(pSoundName);
	if (pMusic == nullptr)
	{

		SDL_Log("FAILED to load the audio\n");
		SDL_Log(Mix_GetError());
		return false;
	}
	Mix_PlayMusic(pMusic, -1);
	return pMusic;
}

//Load Wav file with a given name
Mix_Chunk* SdlEngine::LoadWav(const char* pSoundName)
{
	Mix_Chunk* pTemp = nullptr;
	pTemp = Mix_LoadWAV(pSoundName);
	if (pTemp == nullptr)
	{

		SDL_Log("FAILED to load the audio\n");
		SDL_Log(Mix_GetError());
		return false;
	}
	return pTemp;
}