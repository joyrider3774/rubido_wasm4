#include <stdbool.h>
#include <string.h>
#include "cboardparts.h"
#include "coptionsmenu.h"
#include "cmainmenu.h"
#include "cpeg.h"
#include "cselector.h"
#include "commonvars.h"
#include "wasm4.h"
#include "graphics.h"
#include "helperfuncs.h"
#include "palettes.h"
#include "sound.h"

void drawTitle(bool blitFooter)
{
	setDrawColor(0,0,0,2);
	rect(0,0,SCREEN_SIZE,SCREEN_SIZE);
	setDrawColor(0,0,4,0);
	blit(rubido, (SCREEN_SIZE - rubidoWidth) / 2, 13, rubidoWidth, rubidoHeight, rubidoFlags);
	if(blitFooter)
		blit(willemssoft, (SCREEN_SIZE - willemssoftWidth) / 2, 143, willemssoftWidth, willemssoftHeight, willemssoftFlags);
}

// Load the settings, if there isn't a settings file, set some initial values
void LoadSettings()
{
	savedata.BestPegsLeft[VeryEasy] = 0;
	savedata.BestPegsLeft[Easy] = 0;
	savedata.BestPegsLeft[Hard] = 0;
	savedata.BestPegsLeft[VeryHard] = 0;
	savedata.palindex = 4;
	savedata.sound = 1;
	savedata.inverted = 0;
	diskr(&savedata, sizeof(savedata));
}

// Save the settings
void SaveSettings()
{
	diskw(&savedata, sizeof(savedata));
}

// procedure that calculates how many moves are possible in the current board state
// we can simply do this by checking all parts and see if they can move to all directions
// the canmoveto method in CPegs is does all the checking
int MovesLeft()
{
    CPeg *BoardPart ;
    int TmpMoves=0,Y,X;
    for (Y=0;Y<NrOfRows;Y++)
        for (X=0;X<NrOfCols;X++)
        {
            BoardPart = CBoardParts_GetPart(BoardParts, X,Y);
            // if there is a boardpart on that X,Y Coordinate
            // check all direction if we can move to that if so increases the movesleft
            if (BoardPart)
            {
                if (CPeg_CanMoveTo(BoardPart,X+2,Y,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X-2,Y,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X,Y-2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X,Y+2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X+2,Y-2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X+2,Y+2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X-2,Y+2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X-2,Y-2,false))
                    TmpMoves++;
            }
        }
    return TmpMoves;
}

// Procedure that counts how many pegs are left on the board (animphase must be lower then 2 io a red or blue peg)
int PegsLeft()
{
    CPeg *BoardPart ;
    int Pegs=0,Y,X;
    for (Y=0;Y<NrOfRows;Y++)
        for (X=0;X<NrOfCols;X++)
        {
            BoardPart = CBoardParts_GetPart(BoardParts,X,Y);
            if (BoardPart)
                if ((CPeg_GetType(BoardPart) == IDPeg) && (CPeg_GetAnimPhase(BoardPart) < 2))
                    Pegs++;
        }
    return Pegs;
}

// procedure that draws the board, boardparts info and a boxed message over the playfield
// and waits till the A button is pressed

void PrintForm(char *msg)
{
	PrintFormShown = true;
    setDrawColor(0,0,1,4);
	rect(5,51,150,54);
	setDrawColor(0,0,0,1);
	text(msg,7,53);
}

// this will ceate the initial board state, io a cross of pegs, with the middle on being empty (=animphase 6)
void InitBoard()
{
	CBoardParts_RemoveAll(BoardParts);
    int X,Y;
    for (Y=0;Y < NrOfRows;Y++)
        for (X=0;X < NrOfCols;X++)
        {
            if ((Y < 3) && (X > 2) && (X < 6))
                CBoardParts_Add(BoardParts,CPeg_Create(X,Y));
             if ((Y > 2) && (Y <6))
                CBoardParts_Add(BoardParts,CPeg_Create(X,Y));
            if ((Y > 5) && (X > 2) && (X <6))
                CBoardParts_Add(BoardParts,CPeg_Create(X,Y));
        }
     CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts,4,4), 6);

}

// Checks if we won the game
bool IsWinningGame()
{
    if (PegsLeft() == 1) //must be 1 peg left
    {
        if ((Difficulty == VeryHard) || (Difficulty == Easy))
        {
            if(CPeg_GetAnimPhase(CBoardParts_GetPart(BoardParts,4,4)) < 2) // must be in the middle with veryhard or easy
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

void GameInit()
{
	CSelector_DeSelect(GameSelector);
	CSelector_SetPosition(GameSelector, 4, 4);
	InitBoard();
    Moves = 0;
	mousexPlayField = (*MOUSE_X - XOffSet) / TileWidth;
	mouseyPlayField = (*MOUSE_Y - YOffSet) / TileHeight;
	prevMousexPlayField = mousexPlayField;
	prevMouseyPlayField = mouseyPlayField;
}

// The main Game Loop
void Game()
{
	if( GameState == GSGameInit)
	{
		GameInit();
		GameState -= GSInitDiff;
	}
    char Msg[100];
    setDrawColor(0,0,0,2); 
	rect(0, 0, SCREEN_SIZE, SCREEN_SIZE);
	setDrawColor(0,0,1,1);
	rect(XOffSet-2 + 48, YOffSet-2, 105-53, 148);
	rect(XOffSet-2, YOffSet-2 + 48, 148, 105-53);
    
	setDrawColor(0,0,1,3);
	rect(-4, -4, SCREEN_SIZE+8, 14);
	setDrawColor(0,0,0,1); 
	text("M:", 2, 1);
	citoa(Moves, Msg, 10);
	text(Msg, 20, 1);
	text("L:", 40, 1);
	citoa(MovesLeft(), Msg, 10);
	text(Msg, 60, 1);
	
	text("P:", 84, 1);
	citoa(PegsLeft(), Msg, 10);
	text(Msg, 102, 1);
	if (savedata.BestPegsLeft[Difficulty] != 0)
    {
		text("B:", 124, 1);	
		citoa(savedata.BestPegsLeft[Difficulty], Msg, 10);
		text(Msg, 142, 1);
    }
	CBoardParts_Draw(BoardParts);
	CSelector_Draw(GameSelector);

	//need to repeat showing it until it's no longer shown
	if (PrintFormShown)
	{
		// if it's the winning game play the winning sound and show the form with the winning message
		if (IsWinningGame())
		{
			char win[] = "Congrats, you\nsolved the puzzle!\nNow try a new\ndifficulty!\n\nPress (\x80) to cont.";
			PrintForm(win);
		}
		else // show the loser messager, play loser sound
		{
			char lose[] = "You could not\nsolve the puzzle!\nDon't give up,\ntry it again!\n\nPress (\x80) to cont.";
			PrintForm(lose); 
		}
	}


	if (buttonReleased(BUTTON_LEFT))
	{
		if (!PrintFormShown)
		{
			playGameMoveSound();
			CSelector_SetPosition(GameSelector, CSelector_GetPosition(GameSelector).X -1,CSelector_GetPosition(GameSelector).Y);
		}
	}
    
	if(buttonReleased(BUTTON_RIGHT))
	{
    	if (!PrintFormShown)
		{
			playGameMoveSound();
			CSelector_SetPosition(GameSelector, CSelector_GetPosition(GameSelector).X +1,CSelector_GetPosition(GameSelector).Y);
		}
	}
	
	if(buttonReleased(BUTTON_UP))
	{
		if (!PrintFormShown)
		{
			playGameMoveSound();
			CSelector_SetPosition(GameSelector, CSelector_GetPosition(GameSelector).X,CSelector_GetPosition(GameSelector).Y-1);
		}
	}
	if(buttonReleased(BUTTON_DOWN))
	{
		if (!PrintFormShown)
		{
			CSelector_SetPosition(GameSelector, CSelector_GetPosition(GameSelector).X,CSelector_GetPosition(GameSelector).Y+1);
			playGameMoveSound();
		}
	}

	if(!PrintFormShown)
	{
		mousexPlayField = (*MOUSE_X - XOffSet) / TileWidth;
		mouseyPlayField = (*MOUSE_Y - YOffSet) / TileHeight;
		if ((mousexPlayField != prevMousexPlayField) || (mouseyPlayField != prevMouseyPlayField))
		{
			prevMousexPlayField = mousexPlayField;
			prevMouseyPlayField = mouseyPlayField;
			CSelector_SetPosition(GameSelector, mousexPlayField, mouseyPlayField);
		}
	}
	if(buttonReleased(BUTTON_2) || (mouseButtonReleased(MOUSE_RIGHT) && mouseInGameBounds()))
	{
		if(!PrintFormShown)
		{
			GameState = GSTitleScreenInit;
			playMenuBackSound();
		}
	}
	
	if(buttonReleased(BUTTON_1) || (mouseButtonReleased(MOUSE_LEFT) && 
		((*MOUSE_X >= XOffSet+ ((CSelector_GetPosition(GameSelector).X +0) * TileWidth)) &&
		(*MOUSE_X <= XOffSet+ ((CSelector_GetPosition(GameSelector).X +1) * TileWidth)) &&
		(*MOUSE_Y >= YOffSet+ ((CSelector_GetPosition(GameSelector).Y +0) * TileHeight)) &&
		(*MOUSE_Y <= YOffSet+ ((CSelector_GetPosition(GameSelector).Y +1) * TileHeight)))))

	{
		if(PrintFormShown)
		{
			GameState=GSTitleScreenInit;
			PrintFormShown = false;
			playMenuAcknowlege();
		}
		else
		{
			if (GameSelector->HasSelection) // if we have a selection
			{
				bool cursorCanMoveto = CPeg_CanMoveTo(CBoardParts_GetPart(BoardParts,CSelector_GetSelection(GameSelector).X,CSelector_GetSelection(GameSelector).Y), CSelector_GetPosition(GameSelector).X,CSelector_GetPosition(GameSelector).Y,true); 
				// see if the selected boardpart can move to the current position
				if (cursorCanMoveto)
				{
					playGameAction();
					//if so play a sound, increase the moves, set the selected part to empty and the current part to red
					Moves++;
					CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts,CSelector_GetSelection(GameSelector).X,CSelector_GetSelection(GameSelector).Y), 6);
					CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts,CSelector_GetPosition(GameSelector).X,CSelector_GetPosition(GameSelector).Y), 0);
					// if no moves are left see if the best pegs left value for the current difficulty is
					// greater if so set te new value
					if (MovesLeft() == 0)
					{
						if (savedata.BestPegsLeft[Difficulty] != 0)
						{
							if (PegsLeft() < savedata.BestPegsLeft[Difficulty])
								savedata.BestPegsLeft[Difficulty] = PegsLeft();
						}
						else
							savedata.BestPegsLeft[Difficulty] = PegsLeft();
						// if it's the winning game play the winning sound and show the form with the winning message
						if (IsWinningGame())
						{
							SaveSettings();
							//hack to replay the musical tune
							SelectMusic(musNone, 0);
							SelectMusic(musLevelClear, 0);
							PrintFormShown = true;
						}
						else // show the loser messager, play loser sound
						{
							SaveSettings();
							//hack to replay the musical tune
							SelectMusic(musNone, 0);
							SelectMusic(musFailed, 0);
							PrintFormShown = true;								
						}								
					}

				}
				else // if we can't move to the spot, play the wrong move sound, and reset the selection to a red peg (instead of blue / selected)
				{
					CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts,CSelector_GetSelection(GameSelector).X,CSelector_GetSelection(GameSelector).Y),0);
					playErrorSound();
				}
				CSelector_DeSelect(GameSelector); // deselect the selection
			}
			else // we didn't have a selection, set the new selection
			{
				if (CPeg_GetAnimPhase(CBoardParts_GetPart(BoardParts,CSelector_GetPosition(GameSelector).X,CSelector_GetPosition(GameSelector).Y)) == 0)
				{
					CPeg_SetAnimPhase(CBoardParts_GetPart(BoardParts,CSelector_GetPosition(GameSelector).X,CSelector_GetPosition(GameSelector).Y),1);
					CSelector_Select(GameSelector);
					playGameAction();
				}
			}
		}
	}

    
}

void TitleScreenInit()
{

}

// main title screen loop
void TitleScreen()
{
	if(GameState == GSTitleScreenInit)
	{
		TitleScreenInit();
		GameState -= GSInitDiff;
	}
   
    if(buttonReleased(BUTTON_DOWN))
	{
		CMainMenu_NextItem(Menu);
	}

	if(buttonReleased(BUTTON_UP))
	{
		CMainMenu_PreviousItem(Menu);
	}
	bool mouseok = CMainMenu_SetMouseItem(Menu, *MOUSE_X, *MOUSE_Y);

	if(buttonReleased(BUTTON_1) || (mouseButtonReleased(MOUSE_LEFT) && mouseok))
	{
		// set the gamestate according to the menu selection
		playMenuAcknowlege();
		switch(CMainMenu_GetSelection(Menu))
		{
			case 1:
				GameState = GSDifficultySelectInit;
				break;
			case 2:
				GameState = GSOptionsInit;
				break;
			case 3:
				GameState = GSCreditsInit;
				break;
		}
	}
	drawTitle(true);
	CMainMenu_Draw(Menu);
}

void DifficultySelectInit()
{

}

// Main difficulty select loop
void DifficultySelect()
{
	if(GameState == GSDifficultySelectInit)
	{
		DifficultySelectInit();
		GameState -= GSInitDiff;
	}

    bool rightMouseOk = mouseMovedAtleastOnce() && (*MOUSE_X >= (SCREEN_SIZE - veryhard1Width) / 2) && (*MOUSE_X <= ((SCREEN_SIZE - veryhard1Width) / 2) + veryhard1Width) && (*MOUSE_Y >= 25) && (*MOUSE_Y <= 25 + veryhard1Height);

	if(buttonReleased(BUTTON_2) || ((mouseButtonReleased(MOUSE_RIGHT)) && mouseInGameBounds()))
	{
		playMenuBackSound();
		GameState = GSTitleScreenInit;
	}
	
	if(buttonReleased(BUTTON_1) || (!rightMouseOk && mouseButtonReleased(MOUSE_LEFT) && mouseInGameBounds()))
	{
		playMenuAcknowlege();
		GameState = GSGameInit;
	}
	
	if(buttonReleased(BUTTON_LEFT))
	{
		if(Difficulty == VeryHard)
		{
			Difficulty = Hard;
		}
		else
			if(Difficulty == Hard)
			{
				Difficulty = Easy;
			}
			else
				if(Difficulty == Easy)
				{
					Difficulty = VeryEasy;
				}
				else
					if(Difficulty == VeryEasy)
						Difficulty = VeryHard;
		playMenuSelectSound();
	}	

	if(buttonReleased(BUTTON_RIGHT) || (rightMouseOk && (mouseButtonReleased(MOUSE_LEFT))))
	{
		if(Difficulty == VeryEasy)
		{
			Difficulty = Easy;
		}
		else
			if(Difficulty == Easy)
			{
				Difficulty = Hard;
			}
			else
				if(Difficulty == Hard)
				{
					Difficulty = VeryHard;
				}
				else
					if(Difficulty == VeryHard)
						Difficulty = VeryEasy;
		playMenuSelectSound();
	}
	
	setDrawColor(0,0,0,2);
	rect(0,0,SCREEN_SIZE, SCREEN_SIZE);
	setDrawColor(0,0,0,4);
	blit(leftright, (SCREEN_SIZE - leftrightWidth) / 2, 11, leftrightWidth, leftrightHeight, leftrightFlags);
	blit(movement, 9, 47, movementWidth, movementHeight, movementFlags);
	blit(endposition, 83, 47, endpositionWidth, endpositionHeight, endpositionFlags);
	blit(horzvert, 6, 59, horzvertWidth, horzvertHeight, horzvertFlags);


	// decide what we draw to the buffer based on the difficuly
	switch(Difficulty)
	{
		case VeryEasy:
			setDrawColor(1,2,3,4);
			blit(imganywhere, 81, 81, imganywhereWidth, imganywhereHeight, imganywhereFlags);
			blit(imghorzvertdiag, 0, 81, imghorzvertdiagWidth, imghorzvertdiagHeight, imghorzvertdiagFlags);
			setDrawColor(0,0,0,4);
			blit(anywhere,102, 59, anywhereWidth, anywhereHeight, anywhereFlags);
			blit(diagonal, 22, 67, diagonalWidth, diagonalHeight, diagonalFlags);
			blit(horzvert, 6, 59, horzvertWidth, horzvertHeight, horzvertFlags);
			if(rightMouseOk || !mouseMovedAtleastOnce())
				setDrawColor(0,0,0,3);
			blit(veryeasy1, (SCREEN_SIZE - veryeasy1Width) / 2, 25, veryeasy1Width, veryeasy1Height, veryeasy1Flags);
			break;
		case Easy:
			setDrawColor(1,2,3,4);
			blit(imgmiddle, 81, 81, imgmiddleWidth, imgmiddleHeight, imgmiddleFlags);
			blit(imghorzvertdiag, 0, 81, imghorzvertdiagWidth, imghorzvertdiagHeight, imghorzvertdiagFlags);
			setDrawColor(0,0,0,4);
			blit(middle,105, 59, middleWidth, middleHeight, middleFlags);
			blit(diagonal, 22, 67, diagonalWidth, diagonalHeight, diagonalFlags);
			blit(horzvert, 6, 59, horzvertWidth, horzvertHeight, horzvertFlags);
			if(rightMouseOk || !mouseMovedAtleastOnce())
				setDrawColor(0,0,0,3);
			blit(easy1, (SCREEN_SIZE - easy1Width) / 2, 25, easy1Width, easy1Height, easy1Flags);
			break;
		case Hard:
			setDrawColor(1,2,3,4);
			blit(imganywhere, 81, 81, imganywhereWidth, imganywhereHeight, imganywhereFlags);
			blit(imghorzvert, 0, 81, imghorzvertWidth, imghorzvertHeight, imghorzvertFlags);
			setDrawColor(0,0,0,4);
			blit(anywhere,102, 59, anywhereWidth, anywhereHeight, anywhereFlags);
			blit(horzvert, 6, 59, horzvertWidth, horzvertHeight, horzvertFlags);
			if(rightMouseOk || !mouseMovedAtleastOnce())
				setDrawColor(0,0,0,3);
			blit(hard1, (SCREEN_SIZE - hard1Width) / 2, 25, hard1Width, hard1Height, hard1Flags);
			break;
		case VeryHard:
			setDrawColor(1,2,3,4);
			blit(imgmiddle, 81, 81, imgmiddleWidth, imgmiddleHeight, imgmiddleFlags);
			blit(imghorzvert, 0, 81, imghorzvertWidth, imghorzvertHeight, imghorzvertFlags);
			setDrawColor(0,0,0,4);
			blit(middle,105, 59, middleWidth, middleHeight, middleFlags);
			blit(horzvert, 6, 59, horzvertWidth, horzvertHeight, horzvertFlags);
			if(rightMouseOk || !mouseMovedAtleastOnce())
				setDrawColor(0,0,0,3);
			blit(veryhard1, (SCREEN_SIZE - veryhard1Width) / 2, 25, veryhard1Width, veryhard1Height, veryhard1Flags);
			break;
	}
}

void OptionsInit()
{

}

//Main options loop
void Options()
{
	if(GameState == GSOptionsInit)
	{
		OptionsInit();
		GameState -= GSInitDiff;
	}
   
    if(buttonReleased(BUTTON_DOWN))
	{
		COptionsMenu_NextItem(OptionsMenu);
	}

	if(buttonReleased(BUTTON_UP))
	{
		COptionsMenu_PreviousItem(OptionsMenu);
	}
	
	if(buttonReleased(BUTTON_2) || (mouseButtonReleased(MOUSE_RIGHT) && mouseInGameBounds()))
	{
		playMenuBackSound();
		GameState = GSTitleScreenInit;
	}

	bool mouseok = COptionsMenu_SetMouseItem(OptionsMenu, *MOUSE_X, *MOUSE_Y);

	if(buttonReleased(BUTTON_1) || (mouseButtonReleased(MOUSE_LEFT) && mouseok))
	{
		// set the gamestate according to the menu selection
		playMenuAcknowlege();
		switch(COptionsMenu_GetSelection(OptionsMenu))
		{
			case 1:
				savedata.palindex++;
				if((savedata.palindex >= getMaxPalettes()) || (savedata.palindex < 0))
					savedata.palindex = 0;
				setPalIndex(savedata.palindex);
				SaveSettings();
				break;
			case 2:
				savedata.inverted = !savedata.inverted;
				setPalInverse(savedata.inverted);
				SaveSettings();
				break;
			case 3:
				savedata.sound = !savedata.sound;
				SelectMusic(musNone, 0);
				setSoundOn(savedata.sound);
				setMusicOn(savedata.sound);
				SaveSettings();
				break;
			case 4:
 				GameState = GSTitleScreenInit;
				break;
			default:
				break;
		}
	}
	drawTitle(true);
	COptionsMenu_Draw(OptionsMenu);
}


//Main Credits loop, will just show an image and wait for a button to be pressed
void Credits()
{
	if(buttonReleased(BUTTON_1) || buttonReleased(BUTTON_2) || ((mouseButtonReleased(MOUSE_LEFT) || mouseButtonReleased(MOUSE_RIGHT)) && mouseInGameBounds()))
	{
		playMenuAcknowlege();
		GameState = GSTitleScreenInit;
	}
	drawTitle(false);
	setDrawColor(0,0,4,2);	
	blit(creditstext,  (SCREEN_SIZE - creditstextWidth) / 2, 46, creditstextWidth, creditstextHeight, creditstextFlags);
}

void update()
{
	processSound();
	switch(GameState)
	{
		case GSGameInit:
		case GSGame :
			Game();
			break;
		case GSTitleScreenInit:
		case GSTitleScreen:
			TitleScreen();
			break;
		case GSDifficultySelectInit:
		case GSDifficultySelect:
			DifficultySelect();
			break;
		case GSCreditsInit:
		case GSCredits:
			Credits();
			break;
		case GSOptionsInit:
		case GSOptions:
			Options();
			break;
		default:
			break;
	}
	frames_drawn++;
	updatePrevInputs();
}

// Start of the program, should be obvious what happens here
void start()
{
	updatePrevInputs();
	BoardParts = CBoardParts_Create();
	Menu = CMainMenu_Create();
	OptionsMenu = COptionsMenu_Create();
	GameSelector = CSelector_Create(4,4);
	LoadSettings();
	setMusicOn(savedata.sound);
	setSoundOn(savedata.sound);
	setPalIndex(savedata.palindex);
	setPalInverse(savedata.inverted);
}
