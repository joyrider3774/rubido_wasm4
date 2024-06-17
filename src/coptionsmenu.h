#ifndef COPTIONSMENU_H
#define COPTIONSMENU_H

#include <stdbool.h>

typedef struct COptionsMenu COptionsMenu;

struct COptionsMenu
{
    int Selection; //Holds what we currently selected in the options menu, 1 = color pallet, 2= sound, 3 = music
};

COptionsMenu* COptionsMenu_Create(); // constructor
void COptionsMenu_Draw(COptionsMenu* OptionsMenu); //draw to a certain surface
void COptionsMenu_NextItem(COptionsMenu* OptionsMenu); //Select the next menuitem
void COptionsMenu_PreviousItem(COptionsMenu* OptionsMenu); //select the previous menuitem
int COptionsMenu_GetSelection(COptionsMenu* OptionsMenu); // return the current selection
void COptionsMenu_Destroy(COptionsMenu* OptionsMenu); // destructor
bool COptionsMenu_SetMouseItem(COptionsMenu* OptionsMenu, int mousex, int mousey);
#endif