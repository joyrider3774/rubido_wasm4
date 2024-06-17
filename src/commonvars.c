#include <stdbool.h>
#include "commonvars.h"
#include "cboardparts.h"
#include "cselector.h"
#include "cmainmenu.h"
#include "coptionsmenu.h"


//SDL_Surface *IMGCredits,*IMGPeg,*IMGBackground,*IMGVeryEasy1,*IMGEasy1,*IMGHard1,*IMGVeryHard1,*IMGEasyInfo,*IMGVeryEasyInfo,*IMGHardInfo,*IMGVeryHardInfo;
int Difficulty = VeryEasy;
//Mix_Chunk *Sounds[NrOfSounds]; // array that will hold the sounds

CBoardParts *BoardParts; // boardparts instance that will hold all the boardparts
int GameState = GSTitleScreenInit; // the game state
//Mix_Music *Music; // the music
//SDL_Surface *Screen; // the screen and buffer surface, buffer is used since hardware drawing will be used
//SDL_Surface *Buffer;
int Moves=0;

SaveData savedata;

//FPSmanager FpsManager;

//game
CSelector *GameSelector;
bool PrintFormShown = false;

//titlescreen
CMainMenu* Menu;
COptionsMenu * OptionsMenu;

uint32_t frames_drawn = 0;
int prevMousexPlayField, prevMouseyPlayField, mousexPlayField, mouseyPlayField;