#ifndef CBOARDPARTS_H
#define CBOARDPARTS_H

#include "commonvars.h"
#include "cpeg.h"

typedef struct CBoardParts CBoardParts;
typedef struct CPeg CPeg;

struct CBoardParts
{
 	CPeg *Items[9*9*3]; // array of Cboardparts (nrofrows * norofcols*3)
 	int ItemCount; //how many objects (pegs)
};

CBoardParts* CBoardParts_Create(); 
void CBoardParts_Add(CBoardParts* BoardParts, CPeg *BoardPart); // Add a boardpart
void CBoardParts_Draw(CBoardParts* BoardParts); // Draw all boardparts
CPeg *CBoardParts_GetPart(CBoardParts* BoardParts, const int32_t PlayFieldXin,const int32_t PlayFieldYin); // return a boardpart given the coordinates
void CBoardParts_RemoveAll(CBoardParts* BoardParts); // remove (free) all boardparts
void CBoardParts_CBoardParts_Destroy(CBoardParts* BoardParts);
void CBoardParts_Destroy(CBoardParts* BoardParts);
#endif