#include "wasm4.h"
#include "palettedefines.h"
#include "palettes.h"
#include "helperfuncs.h"

uint8_t palIndex = 0;
uint8_t inverseColors = 0;
Palette pal;

void copyPalette(Palette* dst, Palette* src)
{
	(*dst).Col1 = (*src).Col1;
	(*dst).Col2 = (*src).Col2;
	(*dst).Col3 = (*src).Col3;
	(*dst).Col4 = (*src).Col4;
}

uint8_t getMaxPalettes()
{
    return maxColorSelections;
}

void setPalIndex(uint8_t index)
{
  palIndex = index;
  setPaletteTitle();
}

void setPalInverse(uint8_t value)
{
    inverseColors = value;
    setPaletteTitle();
}

uint8_t getPalInverse()
{
    return inverseColors;
}

uint8_t getPalIndex()
{
  return palIndex;
}


void setPaletteTitle()
{

    switch(palIndex)
    {
		case 0: copyPalette(&pal, &GB_PALETTE); break;
        case 1: copyPalette(&pal, &BLACK_WHITE_PALETTE_TITLE); break;
		case 2: copyPalette(&pal, &GBC_PALETTE_TITLE); break;
		case 3: copyPalette(&pal, &GOLD_PALETTE_TITLE); break;
		case 4: copyPalette(&pal, &WHITE_BLUE_PALETTE_TITLE); break;
		case 5: copyPalette(&pal, &AQUA_PALETTE); break;
		case 6: copyPalette(&pal, &VELVET_PALETTE); break;
		case 7: copyPalette(&pal, &HOLLOW_PALETTE); break;
		case 8: copyPalette(&pal, &GREY_PALETTE); break;
		case 9: copyPalette(&pal, &DEUT_PALETTE); break;
		case 10: copyPalette(&pal, &PROT_PALETTE); break;
		case 11: copyPalette(&pal, &TRIT_PALETTE); break;
		default: copyPalette(&pal, &WHITE_BLUE_PALETTE_TITLE); break;
		
    }

    if(inverseColors)
    {
        Color tmp1 = pal.Col1;
        Color tmp2 = pal.Col2;
        Color tmp3 = pal.Col3;
        Color tmp4 = pal.Col4;

        pal.Col4 = tmp1;
        pal.Col3 = tmp2;
        pal.Col2 = tmp3;
        pal.Col1 = tmp4;
    }
    
    setPalette(pal);
}

const char* getPaletteName()
{
  switch(palIndex)
  {
        case 0: return "COLOR  GB";
        case 1: return "COLOR  BW";
        case 2: return "COLOR  GBC";
        case 3: return "COLOR  GOLD";
        case 4: return "COLOR  BLUE";  
		case 5: return "COLOR  AQUA";
		case 6: return "COLOR  VLVT";
		case 7: return "COLOR  HLOW";
		case 8: return "COLOR  GREY";
		case 9: return "COLOR  DEUT";
		case 10: return "COLOR  PROT";
		case 11: return "COLOR  TRIT";
        default: return "COLOR  BLUE";
  }   
}