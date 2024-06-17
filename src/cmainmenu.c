#include <stdbool.h>
#include <stdlib.h>
#include "cmainmenu.h"
#include "commonvars.h"
#include "wasm4.h"
#include "graphics.h"
#include "helperfuncs.h"
#include "sound.h"

CMainMenu* CMainMenu_Create()
{
	CMainMenu* Result = (CMainMenu*) malloc(sizeof(CMainMenu));
    Result->Selection = 1;
	return Result;
}

 // return the current selection
int CMainMenu_GetSelection(CMainMenu* MainMenu)
{
	return MainMenu->Selection;
}

// Destructor will free the surface images
void CMainMenu_Destroy(CMainMenu* MainMenu)
{
	free(MainMenu);
	MainMenu = NULL ;
}

// Increase the selection if it goes to far set i to the first selection
void CMainMenu_NextItem(CMainMenu* MainMenu)
{
    MainMenu->Selection++;
    if (MainMenu->Selection == 4)
        MainMenu->Selection = 1;
    playMenuSelectSound();
}

// decrease the selection if it goes to low set it to the last selection
void CMainMenu_PreviousItem(CMainMenu* MainMenu)
{
    MainMenu->Selection--;
    if (MainMenu->Selection == 0)
        MainMenu->Selection = 3;
    playMenuSelectSound();
}

bool CMainMenu_SetMouseItem(CMainMenu* MainMenu, int mousex, int mousey)
{
    if((mousex >= (SCREEN_SIZE - newgame1Width) / 2) && (mousex <= ((SCREEN_SIZE - newgame1Width) / 2) + newgame1Width) && (mousey >= 60) && (mousey <= 60+newgame1Height))
	{
		MainMenu->Selection = 1;
		return true;
	}
	if((mousex >= (SCREEN_SIZE - options1Width) / 2) && (mousex <= ((SCREEN_SIZE - options1Width) / 2) + options1Width) && (mousey >= 80) && (mousey <= 80+options1Height))
	{
		MainMenu->Selection = 2;
		return true;
	}
	if((mousex >= (SCREEN_SIZE - credits1Width) / 2) && (mousex <=  ((SCREEN_SIZE - credits1Width) / 2) + credits1Width) && (mousey >= 100) && (mousey <= 100+credits1Height))
	{	MainMenu->Selection = 3;
		return true;
	}
	return false;
}

// Draw the main menu
void CMainMenu_Draw(CMainMenu* MainMenu)
{
    // if selection = newgame draw the purple new game image in the middle of the screen
    if (MainMenu->Selection == 1)
    {
		setDrawColor(0,0,0,3);
    }
    else
    // draw the blue one
    {
		setDrawColor(0,0,0,4);
    }
	blit(newgame1, (SCREEN_SIZE - newgame1Width) / 2, 60, newgame1Width, newgame1Height, newgame1Flags);

	// if selection = options draw the purple options image in the middle of the screen
    if (MainMenu->Selection == 2)
    {
		setDrawColor(0,0,0,3);
    }
    else
    // draw the blue one
    {
		setDrawColor(0,0,0,4);
    }
	blit(options1, (SCREEN_SIZE - options1Width) / 2, 80, options1Width, options1Height, options1Flags);

    if (MainMenu->Selection == 3) // = credits draw purpe
    {
		setDrawColor(0,0,0,3);
    }
    else // blue
    {
		setDrawColor(0,0,0,4);
    }
	blit(credits1, (SCREEN_SIZE - credits1Width) / 2, 100, credits1Width, credits1Height, credits1Flags);

}
