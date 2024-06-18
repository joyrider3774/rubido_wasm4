#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "coptionsmenu.h"
#include "commonvars.h"
#include "wasm4.h"
#include "graphics.h"
#include "helperfuncs.h"
#include "palettes.h"
#include "sound.h"

COptionsMenu* COptionsMenu_Create()
{
	COptionsMenu* Result = (COptionsMenu*) malloc(sizeof(COptionsMenu));
    Result->Selection = 1;
	return Result;
}

 // return the current selection
int COptionsMenu_GetSelection(COptionsMenu* OptionsMenu)
{
	return OptionsMenu->Selection;
}

// Destructor will free the surface images
void COptionsMenu_Destroy(COptionsMenu* OptionsMenu)
{
	free(OptionsMenu);
	OptionsMenu = NULL;
}

// Increase the selection if it goes to far set i to the first selection
void COptionsMenu_NextItem(COptionsMenu* OptionsMenu)
{
    OptionsMenu->Selection++;
    if (OptionsMenu->Selection == 5)
        OptionsMenu->Selection = 1;
    playMenuSelectSound();
}

// decrease the selection if it goes to low set it to the last selection
void COptionsMenu_PreviousItem(COptionsMenu* OptionsMenu)
{
    OptionsMenu->Selection--;
    if (OptionsMenu->Selection == 0)
        OptionsMenu->Selection = 4;
    playMenuSelectSound();
}

bool COptionsMenu_SetMouseItem(COptionsMenu* OptionsMenu, int mousex, int mousey)
{
	//for systems with no mouse movement which could happen in retroarch
	if (!mouseMovedAtleastOnce())
		return false;

    if((mousex >= 38) && (mousex <= 38 + ((int) strlen(getPaletteName())*8)) && (mousey >= 57) && (mousey <= 57+8))
	{
		OptionsMenu->Selection = 1;
		return true;
	}
	if((mousex >= 38) && (mousex <= 38 + (10*8)) && (mousey >= 77) && (mousey <= 77+8))
	{
		OptionsMenu->Selection = 2;
		return true;
	}
	if((mousex >= 38) && (mousex <= 38 + (9*8)) && (mousey >= 97) && (mousey <= 97+8))
	{
		OptionsMenu->Selection = 3;
		return true;
	}
	if((mousex >= 38) && (mousex <= 38 + (4*8)) && (mousey >= 117) && (mousey <= 117+8))
	{
		OptionsMenu->Selection = 4;
		return true;
	}
	return false;
}

// Draw the options menu
void COptionsMenu_Draw(COptionsMenu* OptionsMenu)
{
    // if selection = palettes draw current pallet name
    if (OptionsMenu->Selection == 1)
    {
		setDrawColor(0,0,2,3);
    }
    else
    // draw the blue one
    {
		setDrawColor(0,0,2,4);
    }
	text(getPaletteName(), 38, 57);

	// if selection = sound draw the purple options image in the middle of the screen
    if (OptionsMenu->Selection == 2)
    {
		setDrawColor(0,0,2,3);		
    }
    else
    // draw the blue one
    {
		setDrawColor(0,0,2,4);
    }
	if(savedata.inverted)
		text("INVERT ON", 38, 77);
	else
		text("INVERT OFF", 38, 77);
   

	// if selection = sound draw the purple options image in the middle of the screen
    if (OptionsMenu->Selection == 3)
    {
		setDrawColor(0,0,2,3);		
    }
    else
    // draw the blue one
    {
		setDrawColor(0,0,2,4);
    }
	if(savedata.sound)
		text("SOUND  ON", 38, 97);
	else
		text("SOUND  OFF", 38, 97);
	
	if (OptionsMenu->Selection == 4)
    {
		setDrawColor(0,0,2,3);		
    }
    else
    // draw the blue one
    {
		setDrawColor(0,0,2,4);
    }
	text("BACK", 38, 117);

}
