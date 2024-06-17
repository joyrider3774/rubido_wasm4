#ifndef COMMONVARS_H
#define COMMONVARS_H

#include <stdbool.h>

#include <stdint.h>
#include "cselector.h"
#include "cmainmenu.h"
#include "coptionsmenu.h"

typedef struct CBoardParts CBoardParts;
typedef struct CPeg CPeg;
typedef struct SPoint SPoint;
typedef struct CSelector CSelector;

// The diffrent difficultys
#define VeryEasy 0
#define Easy 1
#define Hard 2
#define VeryHard 3

// The diffrent gameStates possible in the game
#define GSQuit 0
#define GSGame 1 
#define GSTitleScreen 2
#define GSDifficultySelect 3 
#define GSCredits 4
#define GSOptions 5

#define GSInitDiff 50

#define GSGameInit (GSGame + GSInitDiff)
#define GSTitleScreenInit (GSTitleScreen + GSInitDiff)
#define GSDifficultySelectInit (GSDifficultySelect + GSInitDiff)
#define GSCreditsInit (GSCredits + GSInitDiff)
#define GSOptionsInit (GSOptions + GSInitDiff)

//game defines
#define NrOfRows 9
#define NrOfCols 9
#define TileWidth 16
#define TileHeight 16
#define IDPeg 1
#define XOffSet 7
#define YOffSet 13

typedef struct SaveData SaveData;
struct SaveData {
	int BestPegsLeft[4]; // array that holds the best amount of pegs left for each difficulty
	uint8_t palindex;
	uint8_t sound;
	uint8_t music;
	uint8_t inverted;
};

extern int Difficulty;
//extern Mix_Chunk *Sounds[NrOfSounds]; // array that will hold the sounds

extern CBoardParts *BoardParts; // boardparts instance that will hold all the boardparts
extern int GameState; // the game state
extern int Moves;

//game
extern CSelector *GameSelector;
extern bool PrintFormShown;
extern SaveData savedata;

//titlescreen
extern CMainMenu* Menu;
extern COptionsMenu* OptionsMenu;
extern uint32_t frames_drawn;
extern int prevMousexPlayField, prevMouseyPlayField, mousexPlayField, mouseyPlayField;

#endif