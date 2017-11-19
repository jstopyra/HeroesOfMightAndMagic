//Constants.h
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__
#pragma once
//GRID
static const int k_numGridRows = 11;
static const int k_numGridColumns = 15;
static const int k_gridWidth = 44;
static const int k_gridHeight = 42;

//GAMEOBJECTS
static const int k_unitsToSpawnLeft = 11;
	//Components
static const int k_renderableComponentNum = 1;
static const int k_unitComponentNum = 2;
static const int k_transformComponentNum = 3;

//RENDER
	//RenderLayers
static const int k_numRenderLayers = 5;

static const int k_renderLayerBackground = 0;
static const int k_renderLayerPositiveGrid = 1;
static const int k_renderLayerGrid = 2;
static const int k_renderLayerUnits = 3;
static const int k_renderLayerUi = 4;

	//ImagePaths
static const char* k_pCyclops = "Images\\Sprites\\Cyclops.png";
static const char* k_pHeroDark = "Images\\Sprites\\HeroDark.png";
static const char* k_pHeroSilver = "Images\\Sprites\\HeroSilver.png";
static const char* k_pMagog = "Images\\Sprites\\Magog.png";
static const char* k_pHeroesBg = "Images\\HeroesBg.png";
static const char* k_pGrid = "Images\\Grid.png";
static const char* k_pPositiveGrid = "Images\\PositiveGrid.png";
static const char* k_pNegativeGrid = "Images\\NegativeGrid.png";
static const char* k_pNeutralGrid = "Images\\NeutralGrid.png";
static const char* k_pPlayerRight = "Images\\PlayerRight.png";
static const char* k_pPlayerLeft = "Images\\PlayerLeft.png";
static const char* k_pPoint = "Images\\Sprites\\CenterPoint.png";

//SOUNDS
static const char* k_pBgMusic = "Sound\\BackgroundMusic.wav";
static const char* k_pSelectSfx = "Sound\\SelectionSfx.wav";
static const char* k_pAttackSfx = "Sound\\AttackSfx.wav";
static const char* k_pStepSfx = "Sound\\StepSfx.wav";

//TILES
static const int k_tileRadius = 25;
#endif