#ifndef CPEG_H
#define CPEG_H

#include <stdbool.h>
#include "commonvars.h"
#include "cboardparts.h"

typedef struct CBoardParts CBoardParts;
typedef struct CPeg CPeg;

//Base Class that defines a Cboardpart, it's only a peg
struct CPeg
{
 	int32_t Type,PlayFieldX,PlayFieldY,AnimPhase; //Animphase holds the current selected frame of the tile
	int32_t X,Y;
 	CBoardParts *ParentList; // the parentlist, points to a CBoardParts class
};

CPeg* CPeg_Create(const int32_t PlayFieldXin,const int32_t PlayFieldYin);
int32_t CPeg_GetType(CPeg* Peg);
int32_t CPeg_GetX(CPeg* Peg);
int32_t CPeg_GetY(CPeg* Peg);
int32_t CPeg_GetPlayFieldX(CPeg* Peg);
int32_t CPeg_GetPlayFieldY(CPeg* Peg);
int32_t CPeg_GetAnimPhase(CPeg* Peg);
void CPeg_SetAnimPhase(CPeg* Peg,int32_t AnimPhaseIn);
void CPeg_SetPosition(CPeg* Peg,const int32_t PlayFieldXin,const int32_t PlayFieldYin);
bool CPeg_CanMoveTo(CPeg* Peg,const int32_t PlayFieldXin,const int32_t PlayFieldYin,bool erase);
void CPeg_Draw(CPeg* Peg);
void CPeg_Destroy(CPeg* Peg);

#endif