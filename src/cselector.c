#include <stdbool.h>
#include <stdlib.h>
#include "cselector.h"
#include "commonvars.h"
#include "wasm4.h"
#include "helperfuncs.h"
#include "sound.h"

CSelector* CSelector_Create(const int PlayFieldXin,const int PlayFieldYin)
{
	CSelector* Result = (CSelector*) malloc(sizeof(CSelector));
	Result->SelectedPoint.X = 0; // there's no selection set it 0
	Result->SelectedPoint.Y = 0;
	Result->CurrentPoint.X = PlayFieldXin; // set current position
	Result->CurrentPoint.Y = PlayFieldYin;
	Result->HasSelection = false; // No selection when it's created
	return Result;
}

void CSelector_SetPosition(CSelector *Selector, const int PlayFieldXin,const int PlayFieldYin)
{
	// check if the new position is inside the board, if so set the new position as the currentposition
	if (((PlayFieldYin>=0) && (PlayFieldYin < 3) && (PlayFieldXin > 2) && (PlayFieldXin < 6)) ||
		((PlayFieldYin > 2) && (PlayFieldYin<6) && (PlayFieldXin >=0) && (PlayFieldXin <NrOfCols)) ||
		((PlayFieldYin > 5)&& (PlayFieldYin < NrOfRows) && (PlayFieldXin > 2) && (PlayFieldXin <6)))
		{			
			Selector->CurrentPoint.X = PlayFieldXin;
			Selector->CurrentPoint.Y = PlayFieldYin;
		}
}

void CSelector_Select(CSelector *Selector)
{
	Selector->SelectedPoint.X = Selector->CurrentPoint.X;
	Selector->SelectedPoint.Y = Selector->CurrentPoint.Y;
	Selector->HasSelection = true;
}

SPoint CSelector_GetSelection(CSelector *Selector)
{
	return Selector->SelectedPoint;
}

SPoint CSelector_GetPosition(CSelector *Selector)
{
	return Selector->CurrentPoint;
}

void CSelector_DeSelect(CSelector *Selector)
{
	Selector->HasSelection = false;
}

void CSelector_Draw(CSelector *Selector)
{
	setBackForeGroundColor(0, 2);
	rect(XOffSet + 0 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 0 + Selector->CurrentPoint.Y * (TileHeight), TileWidth, TileHeight);
	rect(XOffSet + 1 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 1 + Selector->CurrentPoint.Y * (TileHeight), TileWidth-2, TileHeight-2);	
}

void CSelector_Destroy(CSelector *Selector)
{
	free(Selector);
	Selector = NULL;
}