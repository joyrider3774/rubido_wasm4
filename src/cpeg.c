#include <stdbool.h>
#include <stdlib.h>
#include "cpeg.h"
#include "cboardparts.h"
#include "commonvars.h"
#include "wasm4.h"
#include "graphics.h"
#include "helperfuncs.h"

CPeg* CPeg_Create(const int32_t PlayFieldXin,const int32_t PlayFieldYin)
{
	CPeg* Result = (CPeg*) malloc(sizeof(CPeg));
	Result->Type = IDPeg; // Id, isn't actually used in the game but if u have diffrent boardparts, u can identify it by this
    Result->AnimPhase = 0; // current frame = 0 (a red dot)
 	Result->PlayFieldX=PlayFieldXin; // Set the current playfield position
 	Result->PlayFieldY=PlayFieldYin;
 	Result->X=XOffSet + PlayFieldXin*TileWidth; //set the screen position (for drawing)
 	Result->Y=YOffSet + PlayFieldYin*TileHeight;
 	Result->ParentList = NULL;
	return Result;
}

int32_t CPeg_GetType(CPeg* Peg) 
{
	return Peg->Type;
}

int32_t CPeg_GetX(CPeg* Peg) 
{
	return Peg->X;
}
 	
int32_t CPeg_GetY(CPeg* Peg) 
{
	return Peg->Y;
}
 	
int32_t CPeg_GetPlayFieldX(CPeg* Peg) 
{
	return Peg->PlayFieldX;
}
 	
int32_t CPeg_GetPlayFieldY(CPeg* Peg) 
{
	return Peg->PlayFieldY;
}
 	
int32_t CPeg_GetAnimPhase(CPeg* Peg) 
{
	return Peg->AnimPhase;
}

void CPeg_SetAnimPhase(CPeg* Peg, int32_t AnimPhaseIn) 
{ 
	Peg->AnimPhase = AnimPhaseIn;
}

void CPeg_SetPosition(CPeg* Peg, const int32_t PlayFieldXin,const int32_t PlayFieldYin)
{
	if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
	{
		Peg->PlayFieldX=PlayFieldXin;
		Peg->PlayFieldY=PlayFieldYin;
		Peg->X=XOffSet + PlayFieldXin*TileWidth;
		Peg->Y=YOffSet + PlayFieldYin*TileHeight;
	}
}

bool CPeg_CanMoveTo(CPeg* Peg, const int32_t PlayFieldXin,const int32_t PlayFieldYin,bool erase) 
{
	bool temp;
	temp = true;
	float Xi,Yi;
	int32_t LowX,LowY;
	// if there isn't a boardpart on the specified location
	if (!(CBoardParts_GetPart(Peg->ParentList, PlayFieldXin, PlayFieldYin)))
		return false;
	else
	// if the current frame isn't either a red peg or a blue peg
	if (!(Peg->AnimPhase <2))
		return false;
	else
	//if the place we wan't to move to is an empty peg (animphase = 6)
	if (CPeg_GetAnimPhase(CBoardParts_GetPart(Peg->ParentList,PlayFieldXin,PlayFieldYin)) == 6)
	{
		//calculate the diffrence between the 2 points as a float
		Xi = (float)abs(PlayFieldXin - Peg->PlayFieldX)/2;
		Yi = (float)abs(PlayFieldYin - Peg->PlayFieldY)/2;

		if((Difficulty == VeryHard ) || (Difficulty == Hard))
			// here we see if xi, or yi quals 1 io movement is vertical or horintal and
			// xi or yi is 1. if it isn't 1 this means the new position isn't
			// exactly 2 pegs further away
			temp = temp &&  (((Xi == 0) && (Yi == 1)) || ((Xi ==1) && (Yi == 0)));
		else
			// same as above except we add a diagonal
			temp = temp && (((Xi == 0) && (Yi == 1)) || ((Xi ==1) && (Yi == 0)) || ((Xi==1) && (Yi == 1)));
		
		if (temp)
		{
			// calculate the lowest X & Y coordinate
			// will be used to find the middle peg (io the one we jumped over)
			if (PlayFieldXin <= Peg->PlayFieldX)
				LowX = PlayFieldXin;
			else
				LowX = Peg->PlayFieldX;
			
			if (PlayFieldYin <= Peg->PlayFieldY)
				LowY = PlayFieldYin;
			else
				LowY = Peg->PlayFieldY;

			// if the middle peg doesn't exists
			if (!(CBoardParts_GetPart(Peg->ParentList, LowX+(int32_t)Xi,LowY+(int32_t)Yi)))
			{
				return false;
			}
			else
			{
				// If the middle peg is either a blue (will never happen) or a red peg
				if (CPeg_GetAnimPhase(CBoardParts_GetPart(Peg->ParentList, LowX+(int32_t)Xi,LowY+(int32_t)Yi)) < 2)
				{
					// simple hack to specify we want the middle peg to be emptied (animpahse = 6)
					// i did this so i didn't need to do the above calcultions again in Game()
					if (erase)
					{
						CPeg_SetAnimPhase(CBoardParts_GetPart(Peg->ParentList, LowX+(int32_t)Xi,LowY+(int32_t)Yi),6);
					}
					return true;
				}
			
				else
				{
					return false;
				}
			}
		}
		else
			return false;
	}
	else
		return false;
}

void CPeg_Draw(CPeg* Peg) // drawing
{
	setDrawColor(4,3,2,1);
	blitSub(pegs,Peg->X, Peg->Y, TileWidth, TileHeight, (uint32_t) Peg->AnimPhase * TileWidth, 0, pegsWidth, pegsFlags);
}

void CPeg_Destroy(CPeg* Peg)
{
	free(Peg);
	Peg = NULL ;
}